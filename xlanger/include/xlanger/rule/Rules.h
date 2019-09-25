//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULES_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULES_H

#include "Rule.h"

namespace xlanger::rule
{
	template<RuleIdType _Size>
	struct Rules {
		static constexpr auto Size = _Size;

		Rule rules[Size] = {};

		[[nodiscard]] constexpr const Rule *begin() const
		{ return rules; }

		[[nodiscard]] constexpr const Rule *end() const
		{ return rules + Size; }

		[[nodiscard]] constexpr const Rule &operator[](RuleIdType id) const
		{ return rules[id]; }
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULES_H
