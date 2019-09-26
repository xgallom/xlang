//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULEBUILDER_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULEBUILDER_H

#include "../token/Tokens.h"
#include "Rules.h"

namespace xlanger::rule
{
	template<token::TokenIdType TokensSize, RuleIdType _Size>
	struct RuleBuilder {
		static constexpr auto Size = _Size;

		token::Tokens <TokensSize> tokens = {};
		rule::Rule rules[Size] = {};
		bool hasStart = false;

		template<size_t LhsSize, size_t ... RhsSizes>
		constexpr RuleBuilder<TokensSize, Size + 1> rule(
				const char (&lhs)[LhsSize],
				const char (&... rhs)[RhsSizes]
		) const
		{
			static_assert(sizeof...(RhsSizes), "Empty right hand side of a rule");
			static_assert(sizeof...(RhsSizes) <= Rule::MaxRhs, "Maximum right hand side tokens exceeded");

			const auto lhsToken = tokens(lhs);
			if(!tokens[lhsToken].isNonTerminal())
				throw std::logic_error("Left hand side must be a non terminal");

			bool newHasStart = hasStart;

			if(lhsToken == token::TokenId::Start) {
				if(hasStart)
					throw std::logic_error("Only one rule can produce a Start token");
				else
					newHasStart = true;
			}
			else {
				if constexpr(!Size)
					throw std::logic_error("First rule must produce a Start token");
			}

			return add(Rule{Size, lhsToken, sizeof...(RhsSizes), {tokens(rhs) ...}}, newHasStart);
		}

		template<size_t ... RhsSizes>
		constexpr RuleBuilder<TokensSize, Size + 1> orRhs(const char (&... rhs)[RhsSizes]) const
		{
			static_assert(sizeof...(RhsSizes), "Empty right hand side of a rule");
			static_assert(Size > 0, "Can not create or rule from an empty rule set");

			const auto lhsToken = rules[Size - 1].lhs;

			if(lhsToken == token::TokenId::Start && hasStart)
					throw std::logic_error("Only one rule can produce a Start token");

			return add(Rule{Size, lhsToken, sizeof...(RhsSizes), {tokens(rhs) ...}}, hasStart);
		}

		constexpr Rules <Size> build() const
		{
			Rules <Size> result = {};

			if(!hasStart)
				throw std::logic_error("Rule set does not produce a Start token");

			for(size_t n = 0; n < Size; ++n)
				result.rules[n] = rules[n];

			return result;
		}

	private:
		friend struct RuleBuilder<TokensSize, Size ? Size - 1 : 1>;

		template<token::TokenIdType ATokensSize>
		friend constexpr RuleBuilder<ATokensSize, 0> CreateRuleBuilder(const token::Tokens <ATokensSize> &tokens);

		constexpr RuleBuilder() = default;

		explicit constexpr RuleBuilder(token::Tokens <TokensSize> tokens) : tokens{tokens}
		{}

		constexpr RuleBuilder<TokensSize, Size + 1> add(const Rule &rule, bool newHasStart) const
		{
			RuleBuilder<TokensSize, Size + 1> result = {};
			result.tokens = tokens;

			for(size_t n = 0; n < Size; ++n) {
				if(rules[n] == rule)
					throw std::logic_error("Rule duplication");

				result.rules[n] = rules[n];
			}

			result.rules[Size] = rule;
			result.hasStart = newHasStart;

			return result;
		}
	};

	template<token::TokenIdType TokensSize>
	[[nodiscard]] constexpr RuleBuilder<TokensSize, 0> CreateRuleBuilder(const token::Tokens <TokensSize> &tokens)
	{ return RuleBuilder<TokensSize, 0>{tokens}; }
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_RULEBUILDER_H
