#include "include/world/meter.hpp"

using namespace meter;

Module::Module (flecs::world &ecs){
    /* Register module with world */
    ecs.module<Module>();

    /* Register components */
    ecs.component<Power>();
    ecs.component<Energy>();

    /* Register system */
}