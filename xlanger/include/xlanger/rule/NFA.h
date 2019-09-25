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
	template<token::TokenIdType TokensSize, RuleIdType _RulesSize>
	struct NFA {
		static constexpr auto RulesRootsSize = _RulesSize;
		static constexpr RuleIdType MaxRulesPerRoot = Rule::MaxRhs + 1;
		static constexpr RuleIdType RulesSize = RulesRootsSize * MaxRulesPerRoot;

		using NFARule = rule::NFARule<RulesRootsSize>;

		token::Tokens<TokensSize> tokens = {};
		NFARule rules[RulesSize] = {};
		RuleIdType roots[RulesRootsSize] = {};

		constexpr void computeTransitions()
		{
			for(int n = 0; n < RulesSize; ++n) {
				auto &source = rules[n];

				if(source.isTransitionable()) {
					const auto &transitionToken = tokens[source.transferToken()];

					{
						auto &transition = source.transitions[source.transitionsCount++];
						transition.transferToken = source.transferToken();
						transition.transition = n + 1;
					}

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

	template<token::TokenIdType TokenSize, RuleIdType RulesSize>
	[[nodiscard]] constexpr NFA<TokenSize, RulesSize> CreateNFABuilder(
			const token::Tokens<TokenSize> &tokens,
			const Rules<RulesSize> &rules
	)
	{
		using NFABuilder = rule::NFA<TokenSize, RulesSize>;
		using NFARule = typename NFABuilder::NFARule;

		NFABuilder result = {tokens};

		RuleIdType total = 0;

		for(RuleIdType n = 0; n < NFABuilder::RulesRootsSize; ++n) {
			const auto &source = rules[n];

			result.roots[n] = n * NFABuilder::MaxRulesPerRoot;

			for(RuleIdType i = 0; i <= source.rhsSize; ++i) {
				auto &target = result.rules[n * NFABuilder::MaxRulesPerRoot + i];

				target.id = total++;
				target.lhs = source.lhs;
				target.matchedSize = i;
				target.unmatchedSize = source.rhsSize - i;

				for(typename NFARule::SizeType s = 0; s < source.rhsSize; ++s)
					target.rhs[s] = source.rhs[s];
			}

			for(RuleIdType i = source.rhsSize + 1; i < NFABuilder::MaxRulesPerRoot; ++i) {
				const auto index = n * NFABuilder::MaxRulesPerRoot + i;
				auto &target = result.rules[index];

				target.id = RuleId::Invalid;
			}
		}

		result.computeTransitions();

		return result;
	}
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_NFA_H
