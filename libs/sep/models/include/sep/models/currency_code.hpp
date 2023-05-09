#ifndef __CURRENCY_CODE_H__
#define __CURRENCY_CODE_H__
#include "simple_types.hpp"

namespace sep{
    enum class CurrencyCode : UInt16{
        NA,
        AUSTRAILIAN_DOLLAR = 36,
        CANADIAN_DOLLAR = 124,
        US_DOLLAR = 840,
        EURO = 978
    };
}

#endif // __CURRENCY_CODE_H__