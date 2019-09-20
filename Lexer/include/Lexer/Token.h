//
// Created by Revolware Company on 20/09/2019.
//

#ifndef XLANG_TOKEN_H
#define XLANG_TOKEN_H

#include <cstdint>

namespace Lexer {
	struct Token {
		enum Type : uint8_t {
			Invalid,
			Begin,
			End,
			Number,
			Identifier,
			Plus,
			Minus,
			Asterisk,
			Divide,
			Dot,
			Comma,
			LParen,
			RParen,
			LBracket,
			RBracket,
			LBlock,
			RBlock
		};

		Type type;
	};
}

#endif //XLANG_TOKEN_H
