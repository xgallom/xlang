//
// Created by xgallom on 9/23/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKEN_2_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKEN_2_H

#include "TokenId.h"

namespace xlanger::token
{
	namespace TokenType
	{
		enum Enum {
			Terminal,
			NonTerminal
		};
	}

	struct Token {
		TokenIdType id = {};
		TokenType::Enum type = {};
		size_t nameSize = {};
		const char *name = {};
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKEN_2_H
