#ifndef __GSP_ECS_DCAP_H__
#define __GSP_ECS_DCAP_H__

#include <flecs.h>
#include <ieee-2030.5/device_capability.hpp>

namespace dcap {
    
struct Module {
    Module(flecs::world& world);
};

}
#endif // __GSP_ECS_DCAP_H__