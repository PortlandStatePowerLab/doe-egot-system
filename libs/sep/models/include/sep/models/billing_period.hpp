#ifndef __BILLING_PERIOD_H__
#define __BILLING_PERIOD_H__
#include "date_time_interval.hpp"
#include "simple_types.hpp"

namespace sep {
struct BillingPeriodListLink : ListLink {};
struct ActiveBillingPeriodListLink : ListLink {};
struct BillingPeriodLink : Link {};

///
/// A Billing Period relates to the period of time on which a customer is
/// billed. As an example the billing period interval for a particular customer
/// might be 31 days starting on July 1, 2011. The start date and interval can
/// change on each billing period. There may also be multiple billing periods
/// related to a customer agreement to support different tariff structures.
///
struct BillingPeriod : Resource {
  Int48 bill_last_period;
  Int48 bill_to_date;
  DateTimeInterval interval;
  TimeType status_timestamp;
};
} // namespace sep

#endif // __BILLING_PERIOD_H__
