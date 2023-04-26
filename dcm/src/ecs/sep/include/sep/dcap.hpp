#ifndef __SERVER_H__
#define __SERVER_H__

#include <flecs.h>
#include <string>
#include "fsa.hpp"

namespace sep {
namespace dcap {

std::string serialize (flecs::entity& e);

struct DeviceCapability {};

struct EndDeviceListLink : ListLink {};

struct MirrorUsagePointListLink : ListLink {};

struct SelfDeviceLink : Link {};

struct PollRate{
    UInt32 seconds;
};

struct Test : Link {
    EndDeviceListLink edev;
    MirrorUsagePointListLink mmup;
    SelfDeviceLink sdev;
    PollRate poll;
};

struct Module {
    Module(flecs::world& world);
};

} // namespace dcap
} // namespace sep
#endif // __SERVER_H__