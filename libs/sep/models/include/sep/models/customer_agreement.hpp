#ifndef __CUSTOMER_AGREEMENT_H__
#define __CUSTOMER_AGREEMENT_H__
#include "billing_meter_reading.hpp"
#include "billing_period.hpp"
#include "prepayment.hpp"
#include "reading.hpp"
#include "simple_types.hpp"
#include "tariff_profile.hpp"
#include "time_tariff_interval.hpp"
#include "usage_point_base.hpp"

namespace sep {
struct CustomerAgreementListLink : ListLink {};
struct CustomerAgreementLink : Link {};

///
/// Agreement between the customer and the service supplier to pay for service
/// at a specific service location. It records certain billing information
/// about the type of service provided at the service location and is used
/// during charge creation to determine the type of service.
///
struct CustomerAgreement : IdentifiedObject {
  ActiveBillingPeriodListLink active_billing_period_list_link;
  ActiveProjectionReadingListLink active_projection_reading_list_link;
  ActiveTargetReadingListLink active_target_reading_list_link;
  BillingPeriodListLink billing_period_list_link;
  HistoricalReadingListLink historical_reading_list_link;
  PrepaymentLink prepayment_link;
  ProjectionReadingListLink projection_reading_list_link;
  String42 service_account;
  String42 service_location;
  TargetReadingListLink target_reading_list_link;
  TariffProfileLink tariff_profile_link;
  UsagePointLink usage_point_link;
};
} // namespace sep

#endif // __CUSTOMER_AGREEMENT_H__
