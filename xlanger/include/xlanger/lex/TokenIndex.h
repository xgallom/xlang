//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENINDEX_H
#define XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENINDEX_H

#include "xlanger/token/TokenSize.h"

namespace xlanger::lex
{
	struct TokenIndex {
		size_t beginIndex;
		TokenSize tokenSize;

		void append()
		{ ++tokenSize; }
	};
}

#endif //XLANG_XLANGER_INCLUDE_XLANGER_LEX_TOKENINDEX_H
