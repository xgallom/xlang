//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENID_H
#define XLANG_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENID_H

#include <cstdint>

#ifndef XLANG_XLANGER_TOKEN_ID_TYPE
#define XLANG_XLANGER_TOKEN_ID_TYPE uint8_t
#endif

namespace xlanger::token
{
	using TokenIdType = XLANG_XLANGER_TOKEN_ID_TYPE;
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_TOKEN_TOKENID_H
