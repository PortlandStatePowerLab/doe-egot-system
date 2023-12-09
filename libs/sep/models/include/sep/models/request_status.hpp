#ifndef __REQUEST_STATUS_H__
#define __REQUEST_STATUS_H__
#include "simple_types.hpp"

namespace sep {
///
/// The RequestStatus object is used to indicate the current status of a Flow
/// Reservation Request.
///
struct RequestStatus {
  // Field representing the request status type.
  enum class Status : UInt8 { kRequested, kCancelled };

  TimeType datetime;
  Status status;
};
} // namespace sep

#endif // __REQUEST_STATUS_H__
