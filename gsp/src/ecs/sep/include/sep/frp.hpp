#ifndef __GSP_ECS_FRP_H__
#define __GSP_ECS_FRP_H__

#include <flecs.h>
#include <ieee-2030.5/flow_reservation_response.hpp>

namespace frp {
    
struct Module {
    Module(flecs::world& world);
};

} 
#endif // __GSP_ECS_FRP_H__