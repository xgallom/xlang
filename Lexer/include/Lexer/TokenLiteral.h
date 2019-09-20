//
// Created by Revolware Company on 20/09/2019.
//

#ifndef XLANG_TOKENLITERAL_H
#define XLANG_TOKENLITERAL_H

#include <cstdint>

namespace Lexer {
	struct TokenLiteral {
		enum Type : uint8_t {
			Invalid,
			Whitespace,
			Number,
			Text,
			Operator,
			Separator
		} type;
	};
}
#endif //XLANG_TOKENLITERAL_H
