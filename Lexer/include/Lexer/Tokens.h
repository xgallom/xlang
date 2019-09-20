//
// Created by Revolware Company on 20/09/2019.
//

#ifndef XLANG_TOKENS_H
#define XLANG_TOKENS_H

#include "Token.h"
#include "TokenIndex.h"
#include <vector>

namespace Lexer {
	struct Tokens {
		std::vector<Token> tokens;
		std::vector<TokenIndex> indexes;
	};
}

#endif //XLANG_TOKENS_H
