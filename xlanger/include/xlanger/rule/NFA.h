//
// Created by xgallom on 9/24/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFA_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFA_H

#include "../token/Tokens.h"
#include "NFARule.h"
#include "Rules.h"

namespace xlanger::rule
{
	// TODO: Analysis of memory consumption without std::vector
	template<token::TokenIdType TokensSize, RuleIdType _RulesSize>
	struct NFA {
		static constexpr auto RulesRootsSize = _RulesSize;
		static constexpr RuleIdType MaxRulesPerRoot = Rule::MaxRhs + 1;
		static constexpr RuleIdType RulesSize = RulesRootsSize * MaxRulesPerRoot;

		using NFARule = rule::NFARule<RulesRootsSize>;

		token::Tokens<TokensSize> tokens = {};
		RuleIdType realSize = 0;
		NFARule rules[RulesSize] = {};
		RuleIdType roots[RulesRootsSize] = {};

	private:
		template<token::TokenIdType ATokensSize, RuleIdType ARulesSize>
		friend constexpr NFA<ATokensSize, ARulesSize> CreateNFA(
				const token::Tokens<ATokensSize> &tokens,
				const Rules<ARulesSize> &rules
		);

		constexpr void expandRules(const Rules<RulesRootsSize> &sourceRules)
		{
			RuleIdType total = 0;

			for(RuleIdType n = 0; n < RulesRootsSize; ++n) {
				const auto &source = sourceRules[n];

				roots[n] = total;

				for(RuleIdType i = 0; i <= source.rhsSize; ++i) {
					auto &target = rules[total];

					target.id = total++;
					target.lhs = source.lhs;
					target.matchedSize = i;
					target.unmatchedSize = source.rhsSize - i;

					for(typename NFARule::SizeType s = 0; s < source.rhsSize; ++s)
						target.rhs[s] = source.rhs[s];
				}
			}

			realSize = total;

			for(RuleIdType n = realSize; n < RulesSize; ++n)
				rules[n].id = RuleId::Invalid;
		}

		constexpr void computeTransitions()
		{
			for(int n = 0; n < realSize; ++n) {
				auto &source = rules[n];

				if(source.isTransitionable()) {
					const auto &transitionToken = tokens[source.transferToken()];

					{ // Add first transition to the next rule in the expansion
						auto &transition = source.transitions[source.transitionsCount++];
						transition.transferToken = source.transferToken();
						transition.transition = n + 1;
					}

					// Add transitions to other rule expansions
					if(transitionToken.isNonTerminal()) {
						for(int t = 0; t < RulesRootsSize; ++t) {
							const auto &destination = rules[roots[t]];

							if(destination.isValid() && tokens[destination.lhs].id == transitionToken.id) {
								if(source.transitionsCount == NFARule::MaxTransitions)
									throw std::logic_error("Transition limit per rule exceeded");

								auto &transition = source.transitions[source.transitionsCount++];
								transition.transferToken = token::TokenId::Empty;
								transition.transition = roots[t];
							}
						}
					}
				}
			}
		}
	};

	template<token::TokenIdType TokensSize, RuleIdType RulesSize>
	[[nodiscard]] constexpr NFA<TokensSize, RulesSize> CreateNFA(
			const token::Tokens<TokensSize> &tokens,
			const Rules<RulesSize> &rules
	)
	{
		NFA<TokensSize, RulesSize> result = {tokens};

		result.expandRules(rules);
		result.computeTransitions();

		return result;
	}
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFA_H
