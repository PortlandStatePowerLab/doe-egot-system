#include "include/access_module.hpp"

AccessModule::AccessModule(flecs::world &ecs)
{
    /* Register module with world */
    ecs.module<AccessModule>();

    /* Register components */
    ecs.component<AccessModule::Fingerprint>();
    ecs.component<AccessModule::Subject>();

    /* Register system */
};