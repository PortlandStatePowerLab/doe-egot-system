#ifndef __GSP_ECS_RG_H__
#define __GSP_ECS_RG_H__

#include <flecs.h>
#include <ieee-2030.5/registration.hpp>

namespace rg {
    
struct Module {
    Module(flecs::world& world);
};

}
#endif // __GSP_ECS_RG_H__