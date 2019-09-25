//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULE_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULE_H

#include "../token/TokenId.h"
#include "RuleId.h"

#ifndef XLANG_XLANGER_RULE_RULE_MAX_RHS
#define XLANG_XLANGER_RULE_RULE_MAX_RHS 4
#endif

#ifndef XLANG_XLANGER_RULE_RULE_RHS_SIZE_TYPE
#define XLANG_XLANGER_RULE_RULE_RHS_SIZE_TYPE uint16_t
#endif

namespace xlanger::rule
{
	struct Rule {
		using SizeType = XLANG_XLANGER_RULE_RULE_RHS_SIZE_TYPE;
		static constexpr SizeType MaxRhs = XLANG_XLANGER_RULE_RULE_MAX_RHS;

		RuleIdType id = {};
		token::TokenIdType lhs = {};
		SizeType rhsSize = {};
		token::TokenIdType rhs[MaxRhs] = {};

		[[nodiscard]] constexpr bool operator==(const Rule &o) const
		{ return lhs == o.lhs && rhsSize == o.rhsSize && compare(o); }

	private:
		[[nodiscard]] constexpr bool compare(const Rule &o) const
		{
			for(int n = 0; n < rhsSize; ++n) {
				if(rhs[n] != o.rhs[n])
					return false;
			}

			return true;
		}
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULE_H
