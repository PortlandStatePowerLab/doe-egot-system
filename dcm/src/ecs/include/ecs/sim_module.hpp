#ifndef __SIM_MODULE_H__
#define __SIM_MODULE_H__

#include <flecs.h>

struct simple_module {
    // Define types inside module scope. This is not mandatory, but ensures
    // that their fully qualified Flecs name matches the C++ type name. It also
    // ensures that type names cannot clash between modules.

    struct DER
    {
        unsigned int max_watt_hours;
        int max_import_watts, max_export_watts;
        int max_import_ramp, max_export_ramp;
    };

    struct Energy
    {
        int watt_hours;

    };

    struct Power
    {
        int watts;

    };

    enum class Status : short
    {
        kImporting,
        kExporting,
        kIdle,
        kCustomerOverride
    };

    simple_module(flecs::world& ecs) {


        /* Register module with world */
        ecs.module<simple_module>();

        /* Register components */
        ecs.component<Status>();
        ecs.component<Energy>();
        ecs.component<Power>();
        ecs.component<DER>();

        ecs.set<DER>({1000, 4500, 0, 4500, 0});

        auto q = ecs.query<Status, Energy, Power>("$DER");
     
    }
};

#endif // __SIM_MODULE_H__