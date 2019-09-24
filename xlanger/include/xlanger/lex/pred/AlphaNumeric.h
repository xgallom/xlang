//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_ALPHANUMERIC_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_ALPHANUMERIC_H

#include "Logical.h"
#include "Range.h"

namespace xlanger::lex::pred
{
	template<typename TokenId>
	struct AlphaNumericPredicates {
		static constexpr auto isLower(const Token<TokenId> &token, char c)
		{ return RangePredicates<TokenId>::template range<'a', 'z'>(token, c); }

		static constexpr auto isUpper(const Token<TokenId> &token, char c)
		{ return RangePredicates<TokenId>::template range<'A', 'Z'>(token, c); }

		static constexpr auto isAlpha(const Token<TokenId> &token, char c)
		{ return LogicalPredicates<TokenId>::template either<isLower, isUpper>(token, c); }

		static constexpr auto isNumeric(const Token<TokenId> &token, char c)
		{ return RangePredicates<TokenId>::template range<'0', '9'>(token, c); }

		static constexpr auto isAlNum(const Token<TokenId> &token, char c)
		{ return LogicalPredicates<TokenId>::template either<isAlpha, isNumeric>(token, c); }
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_ALPHANUMERIC_H
