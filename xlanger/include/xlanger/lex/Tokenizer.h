//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENIZER_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENIZER_H

#include "xlanger/token/TokenId.h"

#include <limits>

namespace xlanger::lex
{
	template<typename _TokenId, lex::Predicate<_TokenId> ... _Predicates>
	class Tokenizer {
	public:
		using TokenId = _TokenId;
		using Predicate = lex::Predicate<TokenId>;
		using Token = lex::Token<TokenId>;
		using Self = Tokenizer<_TokenId, _Predicates ...>;
		using ValidTokenIds = typename Token::ValidTokenIds;

		template<typename StreamType>
		using StreamTokenizer = lex::StreamTokenizer<InputStream < StreamType>, Self>;

		static_assert(TokenId::Invalid == sizeof...(_Predicates),
					  "Tokenize must get same amount of predicates as token types");

		static constexpr TokenIdType PredicatesCount = sizeof...(_Predicates);

		static constexpr TokenId tokenIdFor(Token &token, char c)
		{
			for(TokenIdType n = 0; n < PredicatesCount; ++n) {
				typename ValidTokenIds::reference state = token.ids[n];

				if(state) {
					switch(m_predicates[n](token, c)) {
						case PredicateResult::Exact:
							return static_cast<TokenId>(n);

						case PredicateResult::Unsatisfied:
							state = false;
							break;
					}
				}
			}

			return TokenId::Invalid;
		}

		template<typename StreamType>
		static StreamTokenizer<StreamType> createStreamTokenizer(StreamType &inputStream)
		{ return StreamTokenizer<StreamType>({inputStream}); }

		template<typename StreamType>
		StreamTokenizer<StreamType> operator()(StreamType &inputStream) const
		{ return createStreamTokenizer(inputStream); }

		TokenId operator()(char c) const
		{ return tokenIdFor(c); }

	private:
		static constexpr Predicate m_predicates[PredicatesCount] = {_Predicates ...};
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENIZER_H
