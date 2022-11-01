#ifndef __SIMULATION_MODULE_H__
#define __SIMULATION_MODULE_H__


#include <flecs.h>

namespace Simulation
{
    struct Power
    {
        float magnitude;
        float angle;
    };

    struct MaxPower
    {
        int32_t magnitude;
        
    };

    struct Energy 
    {
        float value;
    };

    struct MaxEnergy
    {
        uint32_t value;
    };
    

    struct Module
    {

        Module(flecs::world& ecs);
    };
    
} // namespace Simulation





#endif // __SIMULATION_MODULE_H__