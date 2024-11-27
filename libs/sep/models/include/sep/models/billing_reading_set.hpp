#ifndef __BILLING_READING_SET_H__
#define __BILLING_READING_SET_H__
#include "reading_set_base.hpp"
#include "simple_types.hpp"

namespace sep {
struct BillingReadingListLink : ListLink {};
struct BillingReadingLink : Link {};
struct BillingReadingSetListLink : ListLink {};
struct BillingReadingSetLink : Link {};

///
/// Time sequence of readings of the same reading type.
///
struct BillingReadingSet : ReadingSetBase {
  BillingReadingListLink billing_reading_list_link;
};
} // namespace sep

#endif // __BILLING_READING_SET_H__
