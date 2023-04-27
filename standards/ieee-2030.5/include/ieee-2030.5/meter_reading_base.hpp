#ifndef __METER_READING_BASE_H__
#define __METER_READING_BASE_H__
#include "simple_types.hpp"
#include "reading.hpp"
#include "reading_set_base.hpp"
#include "rate_component.hpp"
#include "reading_type.hpp"

namespace sep
{
    // A container for associating ReadingType, Readings and ReadingSets.
    struct MeterReadingBase : IdentifiedObject{};
    struct MeterReadingListLink : ListLink {};
    struct MeterReadingLink : Link {};

    // Set of values obtained from the meter.
    struct MeterReading : MeterReadingBase {
        RateComponentListLink rate_component_list_link;
        ReadingLink reading_link;
        ReadingSetListLink reading_set_list_link;
        ReadingTypeLink reading_type_link;
    };
    
} // namespace sep

#endif // __METER_READING_BASE_H__