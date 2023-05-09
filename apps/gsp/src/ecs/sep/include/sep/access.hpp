#ifndef __GSP_ECS_ACCESS_H__
#define __GSP_ECS_ACCESS_H__
#include <string>
#include <flecs.h>

namespace access{    
struct Fingerprint{
    std::string value;
};

struct Subject{
    std::string value;
};

struct Done{};

struct Module {
    Module(flecs::world& world);
};
}

#endif // __GSP_ECS_ACCESS_H__