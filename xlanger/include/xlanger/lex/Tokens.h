//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENS_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENS_H

#include "TokenIndex.h"
#include "Token.h"
#include <vector>

namespace xlanger::lex
{
	template<typename _TokenId>
	struct Tokens {
		using TokenId = _TokenId;

		std::vector<TokenId> tokenIds;
		std::vector<TokenIndex> tokenIndexes;
		std::string text;

		void append(TokenId id, const Token <TokenId> &token)
		{
			tokenIds.push_back(id);
			tokenIndexes.push_back(token.index);
		}
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENS_H
