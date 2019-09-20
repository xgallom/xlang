#include <Lexer.h>
#include <iostream>

int main()
{
	std::cout << alignof(Lexer::TokenIndex) << "\n";
	return 0;
}