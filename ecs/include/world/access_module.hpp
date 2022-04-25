#ifndef __ACCESS_MODULE_H__
#define __ACCESS_MODULE_H__

#include <flecs.h>
#include <string>

struct AccessModule
{    
    struct Fingerprint
    {
        std::string value;
    };

    struct Subject
    {
        std::string value;
    };

    AccessModule(flecs::world &ecs);
};

#endif // __ACCESS_MODULE_H__