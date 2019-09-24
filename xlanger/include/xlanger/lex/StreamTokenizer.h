//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_STREAMTOKENIZER_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_STREAMTOKENIZER_H

#include "InputStream.h"
#include "Token.h"
#include "Tokens.h"

namespace xlanger::lex
{
	template<typename _InputStream, typename _Tokenizer>
	class StreamTokenizer {
	public:
		using InputStream = _InputStream;
		using Tokenizer = _Tokenizer;
		using TokenId = typename Tokenizer::TokenId;
		using Token = lex::Token<TokenId>;
		using Tokens = lex::Tokens<TokenId>;

		explicit StreamTokenizer(InputStream inputStream) : m_inputStream{inputStream}
		{}

		Tokens tokenizeAll()
		{
			Tokens result = {};
			Token current = {};
			size_t oldSize = 0;

			current.ids.set();

			do {
				const auto text = readChunk(m_inputStream);

				size_t n = 0;
				for(const auto c : text) {
					const auto tokenId = Tokenizer::tokenIdFor(current, c);

					if(tokenId == TokenId::Invalid) {

					}
					else {
						result.append(tokenId, current);
						current.id = TokenId::Invalid;
						current.index.beginIndex = oldSize + n;
					}

					++n;
				}

				result.text.append(text);
				oldSize = result.text.length();
			} while(false);

			if(current.id != TokenId::Invalid)
				result.append(current);

			return result;
		}

	private:
		InputStream m_inputStream;
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_STREAMTOKENIZER_H
