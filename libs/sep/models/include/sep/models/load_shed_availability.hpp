#ifndef __LOAD_SHED_AVAILABILITY_H__
#define __LOAD_SHED_AVAILABILITY_H__
#include "simple_types.hpp"

namespace sep {
    struct LoadShedAvailabilityListLink : ListLink {};
    struct LoadShedAvailabilityLink : Link {};

    // Indicates current consumption status and ability to shed load.
    struct LoadShedAvailability : Resource {
        // TODO
    };
}

#endif // __LOAD_SHED_AVAILABILITY_H__