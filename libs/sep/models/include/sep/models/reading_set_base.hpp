#ifndef __READING_SET_BASE_H__
#define __READING_SET_BASE_H__
#include "date_time_interval.hpp"
#include "reading.hpp"
#include "simple_types.hpp"

namespace sep {
///
/// A set of Readings of the ReadingType indicated by the parent MeterReading.
/// ReadingBase is abstract, used to define the elements common to ReadingSet
/// and IntervalBlock.</xs:documentation>
///
struct ReadingSetBase : IdentifiedObject {
  DateTimeInterval time_period;
};

struct ReadingSetListLink : ListLink {};
struct ReadingSetLink : Link {};

///
/// A set of Readings of the ReadingType indicated by the
/// parent MeterReading.
///
struct ReadingSet : ReadingSetBase {
  ReadingListLink reading_list_link;
};
} // namespace sep

#endif // __READING_SET_BASE_H__
