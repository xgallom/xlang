//
// Created by Revolware Company on 20/09/2019.
//

#ifndef XLANG_LEXER_H
#define XLANG_LEXER_H

#include "Lexer/Token.h"
#include "Lexer/TokenIndex.h"
#include "Lexer/TokenLiteral.h"
#include "Lexer/Tokens.h"

namespace Lexer {
	Tokens tokenize(const char *input);
}

#endif //XLANG_LEXER_H
