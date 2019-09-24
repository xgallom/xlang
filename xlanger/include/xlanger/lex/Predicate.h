//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_PREDICATE_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_PREDICATE_H

#include "Token.h"

namespace xlanger::lex
{
	namespace PredicateResult
	{
		enum Enum : uint8_t {
			Unsatisfied = 0,
			Satisfied,
			Exact
		};
	}

	template<typename TokenId>
	using Predicate = PredicateResult::Enum (*)(const Token<TokenId> &token, char c);
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_PREDICATE_H
