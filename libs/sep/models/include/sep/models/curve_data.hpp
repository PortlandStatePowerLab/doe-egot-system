#ifndef __CURVE_DATA_H__
#define __CURVE_DATA_H__
#include "simple_types.hpp"

namespace sep {
///
/// Data point values for defining a curve or schedule
///
struct CurveData {
  bool excitation;
  Int32 x_value;
  Int32 y_value;
};

} // namespace sep

#endif // __CURVE_DATA_H__
