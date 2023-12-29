#ifndef __SUBSCRIBABLE_TYPE_H__
#define __SUBSCRIBABLE_TYPE_H__
#include "simple_types.hpp"

namespace sep {
// c++ default enums are 0 as by the standard
enum class SubscribableType : UInt8 {
  kNone,
  kNonConditional,
  kConditional,
  kBoth
};
};     // namespace sep
#endif // __SUBSCRIBABLE_TYPE_H__
