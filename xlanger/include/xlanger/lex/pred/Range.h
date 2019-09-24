//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_RANGE_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_RANGE_H

#include "../Predicate.h"

namespace xlanger::lex::pred
{
	template<typename TokenId>
	struct RangePredicates {
		template<char First, char Last>
		static constexpr auto range(const Token <TokenId> &, char c)
		{ return c >= First && c <= Last ? PredicateResult::Satisfied : PredicateResult::Unsatisfied; }
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_RANGE_H
