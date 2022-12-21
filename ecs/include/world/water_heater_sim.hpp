#ifndef __WATER_HEATER_SIM_H__
#define __WATER_HEATER_SIM_H__

#include <flecs.h>
#include <unordered_map>
#include <string>

namespace waterheater
{
    enum class Status {
        normal,
        loadup,
        advanced_loadup,
        shed,
        critical,
        emergency,
    };

    struct Threshold {
        uint32_t minimum;
        uint32_t maximum;
    };

    struct Nameplate {
        uint32_t power;
        uint32_t gallons;
        uint32_t max_temperature;
        Threshold normal;
        Threshold loadup;
        Threshold advanced_loadup;
        Threshold shed;
        Threshold critical;
        Threshold emergency;
    };

    struct Properties {
        float power;
        float capacity;
    };

    struct Usage {
        std::unordered_map<std::string, float> gallons;
    };

    struct Module
    {
        Module(flecs::world& ecs);
    };
    
} // namespace waterheater

#endif // __WATER_HEATER_SIM_H__