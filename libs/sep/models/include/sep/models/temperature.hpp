#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include "simple_types.hpp"

namespace sep {
///
/// Specification of a temperature.
///
struct Temperature {
  enum class Subject : UInt8 { Enclosure, Transformer, HeatSink };

  PowerOfTenMultiplierType multiplier;
  Subject subject;
  UInt16 value;
};

} // namespace sep

#endif // __TEMPERATURE_H__
