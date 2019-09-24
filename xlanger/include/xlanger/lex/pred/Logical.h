//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_LOGICAL_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_LOGICAL_H

#include "../Predicate.h"

namespace xlanger::lex::pred
{
	template<typename TokenId>
	struct LogicalPredicates {
		template<Predicate<TokenId> ... Predicates>
		static constexpr auto either(const Token<TokenId> &token, char c)
		{ return ((Predicates(token, c)) || ...) ? PredicateResult::Satisfied : PredicateResult::Unsatisfied; }

		template<Predicate<TokenId> ... Predicates>
		static constexpr auto every(const Token<TokenId> &token, char c)
		{ return ((Predicates(token, c)) && ...) ? PredicateResult::Satisfied : PredicateResult::Unsatisfied; }
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_PRED_LOGICAL_H
