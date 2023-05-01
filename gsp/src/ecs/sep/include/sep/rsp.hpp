#ifndef __GSP_ECS_RSP_H__
#define __GSP_ECS_RSP_H__

#include <flecs.h>
#include <ieee-2030.5/response.hpp>

namespace rsp {
    
struct Module {
    Module(flecs::world& world);
};

} 
#endif // __GSP_ECS_RSP_H__