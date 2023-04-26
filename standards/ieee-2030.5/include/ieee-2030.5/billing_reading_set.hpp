#ifndef __BILLING_READING_SET_H__
#define __BILLING_READING_SET_H__
#include "simple_types.hpp"
#include "reading_set_base.hpp"

namespace sep{
    struct BillingReadingListLink : ListLink {};
    struct BillingReadingLink : Link {};
    struct BillingReadingSetListLink : ListLink {};
    struct BillingReadingSetLink : Link {};

    //Time sequence of readings of the same reading type.
    struct BillingReadingSet : ReadingSetBase {
        BillingReadingListLink billing_reading_list_link;
    };
}

#endif // __BILLING_READING_SET_H__