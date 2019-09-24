//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENBUILDER_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENBUILDER_H

#include "Tokens.h"

namespace xlanger::token
{
	template<size_t _Size>
	struct TokenBuilder {
		static constexpr auto Size = _Size;

		Token tokens[Size] = {};

		template<size_t TokenSize>
		[[nodiscard]] constexpr auto terminal(const char (&name)[TokenSize]) const
		{ return add<TokenType::Terminal>(name); }

		template<size_t TokenSize>
		[[nodiscard]] constexpr auto nonTerminal(const char (&name)[TokenSize]) const
		{ return add<TokenType::NonTerminal>(name); }

		[[nodiscard]] constexpr Tokens<Size> build() const
		{
			Tokens<Size> result = {};

			for(size_t n = 0; n < Size; ++n)
				result.tokens[n] = tokens[n];

			return result;
		}

	private:
		friend struct TokenBuilder<Size - 1>;
		friend constexpr TokenBuilder<3> CreateTokenBuilder();

		constexpr TokenBuilder() = default;

		template<TokenType::Enum Type, size_t TokenSize>
		[[nodiscard]] constexpr TokenBuilder<Size + 1> add(const char (&name)[TokenSize]) const
		{
			TokenBuilder<Size + 1> result = {};

			for(size_t n = 0; n < Size; ++n)
				result.tokens[n] = tokens[n];

			result.tokens[Size] = Token{Size, Type, TokenSize, name};

			return result;
		}
	};

	[[nodiscard]] constexpr TokenBuilder<3> CreateTokenBuilder()
	{
		return TokenBuilder<0>()
				.terminal("start")
				.terminal("empty")
				.terminal("invalid");
	}

}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENBUILDER_H
