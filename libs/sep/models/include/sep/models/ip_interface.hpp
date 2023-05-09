#ifndef __IP_INTERFACE_H__
#define __IP_INTERFACE_H__
#include "simple_types.hpp"
namespace sep {
    struct IPInterfaceListLink : ListLink {};
    struct IPInterfaceLink : Link {};
    
    // Specific IPInterface resource.  This resource may be thought of as 
    // network status information for a specific network (IP) layer interface.
    struct IPInterface : Resource {
        // TODO
    };
}

#endif // __IP_INTERFACE_H__