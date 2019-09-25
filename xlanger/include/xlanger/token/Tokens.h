//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENS_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENS_H

#include <cassert>
#include "Token.h"

namespace xlanger::token
{
	template<TokenIdType _Size>
	struct Tokens {
		static constexpr auto Size = _Size;

		Token tokens[Size] = {};

		[[nodiscard]] constexpr const Token *begin() const
		{ return tokens; }

		[[nodiscard]] constexpr const Token *end() const
		{ return tokens + Size; }

		template<size_t N>
		[[nodiscard]] constexpr TokenIdType operator()(const char (&name)[N]) const
		{ return index(name); }

		[[nodiscard]] constexpr const Token &operator[](TokenIdType id) const
		{ return tokens[id]; }

		template<size_t N>
		[[nodiscard]] constexpr TokenIdType index(const char (&name)[N]) const
		{
			for(TokenIdType n = 0; n < Size; ++n) {
				if(tokens[n].compare(name))
					return n;
			}

			const auto fail = [](int n) -> void { n ? throw std::logic_error("Token name not registered") : 0; };

			fail(1);
			return TokenId::Invalid;
		}

		template<size_t N>
		[[nodiscard]] constexpr const Token &at(const char (&name)[N]) const
		{ return tokens[index(name)]; }
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENS_H
