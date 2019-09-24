//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENS_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENS_H

#include <cassert>
#include "Token.h"

namespace xlanger::token
{
	template<size_t _Size>
	struct Tokens {
		static constexpr auto Size = _Size;

		Token tokens[Size] = {};

		[[nodiscard]] constexpr const Token *begin() const { return tokens; }
		[[nodiscard]] constexpr const Token *end() const { return tokens + Size; }

		template<size_t N>
		[[nodiscard]] constexpr const Token &operator()(const char (&name)[N]) const
		{
			for(int n = 0; n < Size; ++n) {
				if(Compare(tokens[n].nameSize, tokens[n].name, name))
					return tokens[n];
			}
		}

		template<size_t N>
		static constexpr bool Compare(size_t nameSize, const char *name, const char (&key)[N])
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

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENS_H
