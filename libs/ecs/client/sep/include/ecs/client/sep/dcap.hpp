#ifndef __SERVER_H__
#define __SERVER_H__

#include <flecs.h>
#include <string>
#include <sep/models/device_capability.hpp>

namespace dcap {

void deserialize (flecs::iter &it, const sep::DeviceCapability &dcap);
    
struct Module {
    Module(flecs::world& world);
};

} // namespace dcap
#endif // __SERVER_H__