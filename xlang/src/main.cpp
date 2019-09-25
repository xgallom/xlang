#include <iostream>
#include <xlanger/xlanger.h>

int main(int argc, char *argv[])
{
	// Implement updates as rule builder functions that add functions

	constexpr auto tokens = xlanger::token::CreateTokenBuilder()/*
			.nonTerminal("Program")
			.nonTerminal("Function")
			.nonTerminal("Statement")

			.terminal("function")

			.terminal("identifier")
			.terminal("number")

			.terminal(":")*/
			.terminal("a")
			.terminal("b")
			.terminal("c")
			.terminal("d")

			.nonTerminal("A")
			.nonTerminal("S")

			.build();

	constexpr auto rules = xlanger::rule::CreateRuleBuilder(tokens)/*
			.rule("Start", "Program", "end")

			.rule("Program", "Program", "Function")
			.rule("Program", "empty")

			.rule("Function", "function", "identifier", ":", "Statement")*/
			.rule("Start", "S")

			.rule("S", "a", "A", "c")
			.orRhs("b", "A", "d", "d")

			.rule("A", "b")

			.build();

	constexpr auto nfaBuilder = xlanger::rule::CreateNFABuilder(tokens, rules);

	std::cout << "tokens:\n";
	for(const auto &token : tokens)
		std::cout << "  " << int(token.id) << ": " << token.type << " " << token.name << "[" << token.nameSize << "]\n";

	std::cout << "\nrules:\n";
	for(const auto &rule : rules) {
		std::cout << "  " << rule.id << ": " << tokens[rule.lhs].name << " => ";
		for(size_t n = 0; n < rule.rhsSize; ++n)
			std::cout << tokens[rule.rhs[n]].name << " ";
		std::cout << "\n";
	}

	std::cout << "\nNFA:\n";
	std::cout << "  rules:\n";
	for(const auto &rule : nfaBuilder.rules) {
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
				const auto &destination = nfaBuilder.rules[rule.transitions[t].transition];
				std::cout << "      " << tokens[rule.transitions[t].transferToken].name << " -> "
						  << destination.id << "\n";
			}
		}
	}

	std::cout << "  roots:\n";
	for(const auto &root : nfaBuilder.roots)
		std::cout << "    " << nfaBuilder.rules[root].id << "\n";

	return 0;
}