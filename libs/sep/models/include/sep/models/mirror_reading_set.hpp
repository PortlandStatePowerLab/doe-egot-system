#ifndef __MIRROR_READING_SET_H__
#define __MIRROR_READING_SET_H__
#include "reading.hpp"
#include "reading_set_base.hpp"

namespace sep {
///
/// A set of Readings of the ReadingType indicated by the parent MeterReading.
///
struct MirrorReadingSet : ReadingSetBase {
  Reading reading;
};

} // namespace sep

#endif // __MIRROR_READING_SET_H__
