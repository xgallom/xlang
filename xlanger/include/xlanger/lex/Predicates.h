//
// Created by xgallom on 9/20/19.
//

#ifndef XLANG_ROOT_XLANGER_INCLUDE_XLANGER_LEX_PRED_PREDICATES_H
#define XLANG_ROOT_XLANGER_INCLUDE_XLANGER_LEX_PRED_PREDICATES_H

#include "pred/pred.h"

namespace xlanger::lex
{
	template<typename _TokenId>
	struct Predicates :
			pred::AlphaNumericPredicates<_TokenId>,
			pred::DiscreetPredicates<_TokenId>,
			pred::LiteralPredicates<_TokenId>,
			pred::LogicalPredicates<_TokenId>,
			pred::RangePredicates<_TokenId> {
		using TokenId = _TokenId;
		using Token = lex::Token<TokenId>;
	};
}

#endif //XLANG_ROOT_XLANGER_INCLUDE_XLANGER_LEX_PRED_PREDICATES_H
