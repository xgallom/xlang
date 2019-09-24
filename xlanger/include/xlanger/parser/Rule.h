//
// Created by xgallom on 9/23/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_PARSER_RULE_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_PARSER_RULE_H

namespace xlanger::parser
{
	template<typename TokenId>
	static constexpr auto createStartRule()
	{
		return std::tuple(TokenId::Start);
	}

	template<typename TokenId, typename ... TokenTypes>
	static constexpr auto createRule(TokenTypes &... tokens)
	{
		return std::tuple<TokenTypes &...>(tokens ...);
	}
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_RULE_H
