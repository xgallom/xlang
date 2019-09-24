//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKEN_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKEN_H

#include "TokenIndex.h"
#include <bitset>

namespace xlanger::lex
{
	template<typename _TokenId>
	struct Token {
		using TokenId = _TokenId;
		using ValidTokenIds = std::bitset<TokenId::Invalid>;

		ValidTokenIds ids = {};
		TokenIndex index = {};
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKEN_H
