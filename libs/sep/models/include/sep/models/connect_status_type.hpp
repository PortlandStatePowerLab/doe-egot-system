#ifndef __CONNECT_STATUS_TYPE_H__
#define __CONNECT_STATUS_TYPE_H__
#include "simple_types.hpp"

namespace sep {
struct ConnectStatusType {
  enum class Status : HexBinary16 {
    kConnected = 0,
    kAvailable = 1 << 0,
    kOperating = 1 << 1,
    kTest = 1 << 2,
    kFaultError = 1 << 3
  };

  TimeType date_time;
  Status value;
};

} // namespace sep

#endif // __CONNECT_STATUS_TYPE_H__
