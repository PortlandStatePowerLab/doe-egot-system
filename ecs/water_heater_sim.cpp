#include "include/world/water_heater_sim.hpp"
#include "include/world/meter.hpp"

using namespace waterheater;

float INLET_WATER_TEMP = 10; // degrees C
float AMBIENT_AIR_TEMP = 21; // degrees C
float SPECIFIC_HEAT = 4.187; // kJ/kgK
float KG_PER_GALLON = 3.79;  // kg/gallon

float fahrenheit2Celcius(const float &temperature)
{
    return (32.0 - temperature) * 5 / 9;
}

float gallon2Kilogram(const float &gallons)
{
    return KG_PER_GALLON * gallons;
}

float energy(const float &mass)
{
    float dt = AMBIENT_AIR_TEMP - INLET_WATER_TEMP;
    return SPECIFIC_HEAT * dt * mass;
}

Module::Module(flecs::world &ecs)
{
    /* Register module with world */
    ecs.module<Module>();
    ecs.import <meter::Module>();

    /* Register components */
    ecs.component<Status>();
    ecs.component<Nameplate>();
    ecs.component<Properties>();
    ecs.component<Usage>();

    /* Register system */
    ecs.system<const Nameplate, meter::Power, meter::Energy>("Usage")
        .term(Status::normal)
        .each([](flecs::entity e, Nameplate &rating, meter::Power *power, meter::Energy *energy) {

        });

    ecs.system<const Nameplate, meter::Power, meter::Energy>("Normal")
        .term(Status::normal)
        .each([](flecs::entity e, Nameplate &rating, meter::Power *power, meter::Energy *energy) {

        });
}