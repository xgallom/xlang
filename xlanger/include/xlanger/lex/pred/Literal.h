//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_LEX_PRED_LITERAL_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_LEX_PRED_LITERAL_H

#include "../Predicate.h"

namespace xlanger::lex::pred
{
	template<size_t _Size>
	struct String {
		static constexpr auto
				Size = _Size,
				Length = Size - 1;

		constexpr String() = default;

		char text[Size] = {};
	};

	template<size_t Size>
	constexpr String<Size> literal(const char (&string)[Size])
	{
		String<Size> result;

		for(size_t n = 0; n < Size; ++n)
			result.text[n] = string[n];

		return result;
	}

	template<typename TokenId>
	struct LiteralPredicates {
		template<size_t Size>
		static constexpr String<Size> literal(const char (&string)[Size])
		{ return pred::literal(string); }

		template<auto Literal>
		static constexpr PredicateResult::Enum isLiteral(const Token <TokenId> &token, char c)
		{
			using String = typeof(Literal);

			if(token.index.tokenSize >= String::Length)
				return PredicateResult::Unsatisfied;

			//std::cout << token.index.tokenSize << ": " << (c == Literal.text[token.index.tokenSize]) << "\n";

			return c == Literal.text[token.index.tokenSize] ?
				   (token.index.tokenSize == String::Length - 1 ? PredicateResult::Exact : PredicateResult::Satisfied) :
				   PredicateResult::Unsatisfied;
		}
	};

}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_LEX_PRED_LITERAL_H
