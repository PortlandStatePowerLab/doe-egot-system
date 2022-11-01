#ifndef __DER_H__
#define __DER_H__

#include <cstdint>
#include <flecs.h>

namespace DER
{
    struct RealPower
    {
        float value;
    };

    struct ReactivePower
    {
        float value;
    };

    // assume +/- boundary for max power
    struct MaxRealPower
    {
        uint32_t value;
    };

    // assume +/- boundary for max power
    struct MaxReactivePower
    {
        uint32_t value;
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

} // namespace DER

#endif // __DER_H__