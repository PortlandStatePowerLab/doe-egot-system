#ifndef __BILLING_METER_READING_H__
#define __BILLING_METER_READING_H__
#include "simple_types.hpp"
#include "meter_reading_base.hpp"
#include "reading_type.hpp"
#include "billing_reading_set.hpp"

namespace sep{
    struct BillingMeterReadingBase : MeterReadingBase {
        BillingReadingSetListLink billing_reading_set_list_link;
        ReadingTypeLink reading_type_link;
    };

    struct ProjectionReading : BillingMeterReadingBase {};
    struct ProjectionReadingListLink : ListLink {};
    struct ProjectionReadingLink : Link {};
    struct ActiveProjectionReadingListLink : ListLink {};
    struct ActiveProjectionReadingLink : Link {};

    struct TargetReading : BillingMeterReadingBase {};
    struct TargetReadingListLink : ListLink {};
    struct TargetReadingLink : Link {};
    struct ActiveTargetReadingListLink : ListLink {};
    struct ActiveTargetReadingLink : Link {};

    struct HistoricalReading : BillingMeterReadingBase {};
    struct HistoricalReadingListLink : ListLink {};
    struct HistoricalReadingLink : Link {};
}

#endif // __BILLING_METER_READING_H__