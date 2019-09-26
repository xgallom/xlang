#include <iostream>
#include <xlanger/xlanger.h>
#include <vector>

int main(int argc, char *argv[])
{
	// TODO: Implement updates as rule builder functions that add functions

	constexpr auto tokens = xlanger::token::CreateTokenBuilder()
			.terminal("a")
			.terminal("b")
			.terminal("c")
			.terminal("d")

			.nonTerminal("A")
			.nonTerminal("S")/*

			.terminal("number")
			.terminal("+")
			.terminal("-")

			.nonTerminal("Expr")*/

			.build();

	constexpr auto rules = xlanger::rule::CreateRuleBuilder(tokens)
			.rule("Start", "S")

			.rule("S", "a", "A", "c")
			.orRhs("b", "A", "d", "d")

			.rule("A", "b")/*

			.rule("Start", "Expr")

			.rule("Expr", "number")
			.rule("Expr", "Expr", "+", "Expr")
			.rule("Expr", "Expr", "-", "Expr")*/

			.build();

	constexpr auto nfa = xlanger::rule::CreateNFA(tokens, rules);

	std::cout << "tokens:\n";
	for(const auto &token : tokens)
		std::cout << "  " << int(token.id) << ": " << token.type << " " << token.name << "\n";

	std::cout << "\nrules:\n";
	for(const auto &rule : rules) {
		std::cout << "  " << rule.id << ": " << tokens[rule.lhs].name << " => ";
		for(size_t n = 0; n < rule.rhsSize; ++n)
			std::cout << tokens[rule.rhs[n]].name << " ";
		std::cout << "\n";
	}

	std::cout << "\nNFA:\n";
	std::cout << "  rules:\n";
	for(const auto &rule : nfa.rules) {
		if(rule.id == xlanger::rule::RuleId::Invalid)
			continue;

		std::cout << "    " << rule.id << ": " << tokens[rule.lhs].name << " => ";
		for(size_t n = 0; n < rule.matchedSize; ++n)
			std::cout << tokens[rule.rhs[n]].name << " ";
		std::cout << "| ";
		for(size_t n = rule.matchedSize; n < rule.rhsSize(); ++n)
			std::cout << tokens[rule.rhs[n]].name << " ";
		std::cout << "\n";

		if(rule.transitionsCount) {
			for(int t = 0; t < rule.transitionsCount; ++t) {
				const auto &destination = nfa.rules[rule.transitions[t].transition];
				std::cout << "      " << tokens[rule.transitions[t].transferToken].name << " -> "
						  << destination.id << "\n";
			}
		}
	}

	std::cout << "  roots:\n";
	for(const auto &root : nfa.roots)
		std::cout << "    " << nfa.rules[root].id << "\n";

	xlanger::token::Tokens<4> string = {
			tokens.at("b"),
			tokens.at("b"),
			tokens.at("d"),
			tokens.at("d")
	};

	struct Stack {
		std::vector<xlanger::rule::RuleIdType> ruleStack = {};
		xlanger::token::TokenIdType currentToken = 0;

		bool tryContinue(const xlanger::token::Tokens<4> &string,
				const xlanger::rule::NFA<10, 4> &nfa,
				std::vector<Stack> &children
				) {
			const auto &token = string[currentToken++];

			if(currentToken == ) // TODO: Finished here

			const auto &rule = nfa.rules[ruleStack.back()];

			for(xlanger::rule::RuleIdType t = 0; t < rule.transitionsCount; ++t) {
				const auto &transition = rule.transitions[t];

				xlanger::token::TokenIdType transitionToken = transition.transferToken;

				if(transitionToken == xlanger::token::TokenId::Empty)
					transitionToken = nfa.rules[transitionToken].lhs;

				if(transitionToken == token.id) {
					auto newChild = *this;
					newChild.ruleStack.push_back(transition.transition);
					children.push_back(newChild);
				}
			}

			return false;
		}
	};

	std::cout << "\n";
	std::vector<Stack> stacks = {Stack{}};
	for(;;) {
		if(stacks.empty())
			break;

		std::vector<Stack> children = {};
		for(auto &stack : stacks) {
			if(stack.tryContinue(string, nfa, children))
				break;
		}

		stacks = children;
	}

	std::cout << "\nStacks: " << stacks.size() << "\n";
	for(const auto &stack : stacks) {
		std::cout << "  " << stack.ruleStack
	}

	return 0;
}