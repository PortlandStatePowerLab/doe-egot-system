#ifndef __GSP_ECS_EDEV_H__
#define __GSP_ECS_EDEV_H__

#include <flecs.h>
#include <ieee-2030.5/end_device.hpp>

namespace edev {
    
struct Module {
    Module(flecs::world& world);
};

} 
#endif // __GSP_ECS_EDEV_H__