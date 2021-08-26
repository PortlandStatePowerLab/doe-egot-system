#ifndef __SEP_MODULE_H__
#define __SEP_MODULE_H__
#include <flecs.h>
#include <string>

// Define types inside module scope. This is not mandatory, but ensures
// that their fully qualified Flecs name matches the C++ type name. It also
// ensures that type names cannot clash between modules.
struct SEPModule
{
    struct Link
    {
        std::string href;
    };

    struct ListLink
    {
        uint32_t all;
        std::string href;
    };

    struct FlowReservationResponse
    {
        
    };

    SEPModule (flecs::world &ecs)
    {
        ecs.module <SEPModule>();

        ecs.component <Link>();
    }
};

#endif // __SEP_MODULE_H__