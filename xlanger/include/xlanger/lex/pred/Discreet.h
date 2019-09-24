//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_DISCREET_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_DISCREET_H

#include "../Predicate.h"

namespace xlanger::lex::pred
{
	template<typename TokenId>
	struct DiscreetPredicates {
		template<char ... Characters>
		static constexpr auto oneOf(const Token <TokenId> &, char c)
		{ return ((c == Characters) || ...) ? PredicateResult::Satisfied : PredicateResult::Unsatisfied; }

		template<char Character>
		static constexpr auto is(const Token <TokenId> &, char c)
		{ return c == Character ? PredicateResult::Satisfied : PredicateResult::Unsatisfied; }
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_DISCREET_H
