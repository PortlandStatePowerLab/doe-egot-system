#ifndef __WATERHEATER_H__
#define __WATERHEATER_H__

#include <flecs.h>

namespace WaterHeater
{
    enum State
    {
        Idle,
        Shed,
        LoadUp
    };

    struct Module
    {
        Module(flecs::world& ecs);
    };
} // namespace Simulator

#endif // __WATERHEATER_H__