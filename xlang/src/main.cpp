#include <iostream>
#include <xlanger/xlanger.h>

int main(int argc, char *argv[])
{
	constexpr auto tokens = xlanger::token::CreateTokenBuilder()
			.terminal("number")
			.terminal("")
			.build();

	constexpr const auto token = tokens("number");

	std::cout << int(token.id) << ": " << token.type << ", " << token.nameSize << ", " << token.name << "\n";

	return 0;
}