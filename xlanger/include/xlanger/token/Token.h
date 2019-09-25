//
// Created by xgallom on 9/23/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKEN_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKEN_H

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

		[[nodiscard]] explicit constexpr operator bool() const
		{ return id != TokenId::Invalid; }

		[[nodiscard]] constexpr bool isTerminal() const
		{ return type == TokenType::Terminal; }

		[[nodiscard]] constexpr bool isNonTerminal() const
		{ return type == TokenType::NonTerminal; }

		template<size_t N>
		constexpr bool compare(const char (&key)[N]) const
		{
			if(nameSize != N)
				return false;

			for(size_t n = 0; n < N; ++n)
				if(name[n] != key[n])
					return false;

			return true;
		}
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKEN_H
