#include "include/sep/access.hpp"

namespace access {
Module::Module(flecs::world &ecs)
{
    /* Register module with world */
    ecs.module<Module>();

    /* Register components */
    ecs.component<Fingerprint>();
    ecs.component<Subject>();

    /* Register system */
};
}