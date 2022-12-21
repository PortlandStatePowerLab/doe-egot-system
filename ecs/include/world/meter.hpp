#ifndef __METER_H__
#define __METER_H__

#include <flecs.h>

namespace meter
{
    struct Power {
        float watts;
        float vars;
    };

    struct Energy {
        float watt_hours;
    };

    struct Module
    {
        Module(flecs::world& ecs);
    };
} // namespace meter

#endif // __METER_H__