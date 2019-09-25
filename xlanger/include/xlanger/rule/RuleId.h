//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULEID_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULEID_H

#ifndef XLANG_XLANGER_RULE_ID_TYPE
#define XLANG_XLANGER_RULE_ID_TYPE uint16_t
#endif

namespace xlanger::rule
{
	using RuleIdType = XLANG_XLANGER_RULE_ID_TYPE;

	namespace RuleId
	{
		enum Enum {
			Invalid = std::numeric_limits<RuleIdType>::max()
		};
	}
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULEID_H
