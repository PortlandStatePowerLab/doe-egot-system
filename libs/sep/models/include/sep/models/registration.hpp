#ifndef __REGISTRATION_H__
#define __REGISTRATION_H__
#include "pin_type.hpp"
#include "simple_types.hpp"

namespace sep {
struct RegistrationListLink : ListLink {};
struct RegistrationLink : Link {};

///
/// Registration represents an authorization to access the resources on a host.
///
struct Registration : Resource {
  TimeType date_time_registered;
  PINType pin;
  UInt32 poll_rate = 900;
};

} // namespace sep

#endif // __REGISTRATION_H__
