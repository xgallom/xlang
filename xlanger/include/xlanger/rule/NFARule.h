//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFARULE_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFARULE_H

#include "Rule.h"
#include "NFATransition.h"

namespace xlanger::rule
{
	template<RuleIdType _MaxTransitions>
	struct NFARule {
		using SizeType = Rule::SizeType;
		static constexpr auto MaxRhs = Rule::MaxRhs;
		static constexpr auto MaxTransitions = _MaxTransitions;

		RuleIdType id = {};
		token::TokenIdType lhs = {};
		SizeType matchedSize = {};
		SizeType unmatchedSize = {};
		token::TokenIdType rhs[MaxRhs] = {};
		RuleIdType transitionsCount = {};
		NFATransition transitions[MaxTransitions] = {};

		[[nodiscard]] constexpr SizeType rhsSize() const
		{ return matchedSize + unmatchedSize; }

		[[nodiscard]] constexpr token::TokenIdType transferToken() const
		{ return rhs[matchedSize]; }

		[[nodiscard]] constexpr bool isValid() const
		{ return id != RuleId::Invalid; }

		[[nodiscard]] constexpr bool isTransitionable() const
		{ return isValid() && unmatchedSize > 0; }
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFARULE_H
