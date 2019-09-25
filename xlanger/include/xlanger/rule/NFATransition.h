//
// Created by xgallom on 9/25/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFATRANSITION_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFATRANSITION_H

#include "../token/TokenId.h"
#include "RuleId.h"

namespace xlanger::rule
{
	struct NFATransition {
		token::TokenIdType transferToken = {};
		RuleIdType transition = {};
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFATRANSITION_H
