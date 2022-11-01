#include "include/waterheater.hpp"
#include "include/der.hpp"
#include <iostream>
#include <random>
#include <chrono>

static uint64_t getTime()
{
    uint64_t seconds = std::chrono::duration_cast<std::chrono::seconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();
    std::cout << "Time : " << seconds << "/n";
    return seconds;
};

namespace WaterHeater
{
    Module::Module(flecs::world &ecs)
    {
        ecs.module<Module>();
        ecs.import <DER::Module>();

        ecs.component<State>().add(flecs::Union);

        ecs.system<DER::RealPower, DER::MaxEnergy, DER::Energy>("Idle")
            .term<State>(Idle)
            .each([](flecs::entity e, DER::RealPower &pwr, DER::MaxEnergy &limit, DER::Energy &energy)
                  {
                pwr.value = 0;
                // TODO: have usage follow actual customer pattern rather than random
                // I used 1/4 the max energy for shed to make it quicker.
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_int_distribution<unsigned int> dist(1, 10);

                energy.value += dist(eng);
                if (energy.value > limit.value){
                    e.add(WaterHeater::State::LoadUp);
                } });

        ecs.system<DER::RealPower, DER::MaxRealPower, DER::MaxEnergy, DER::Energy>("Shed")
            .term<State>(Shed)
            .each([](flecs::entity e, DER::RealPower &pwr, DER::MaxRealPower &pwr_limit, DER::MaxEnergy &energy_limit, DER::Energy &energy)
                  {
                // TODO: have usage follow actual customer pattern rather than random
                // I used 1/4 the max energy for shed to make it quicker.
                if (getTime() % 10 == 0)
                {
                    std::random_device rd;
                    std::default_random_engine eng(rd());
                    std::uniform_int_distribution<unsigned int> dist(1, energy_limit.value);

                    energy.value += dist(eng);
                }

                float delta_time = 1.0 / 3600.0; // hours
                if (energy.value > energy_limit.value){
                    pwr.value = pwr_limit.value;
                    energy.value -= pwr.value*delta_time;
                }
                else 
                {
                    pwr.value = 0;
                }
                std::cout << "Energy Value : " << energy.value << " and Power Value : " << pwr.value << "\n"; });

        ecs.system<DER::RealPower, DER::MaxRealPower, DER::Energy>("LoadUp")
            .term<State>(LoadUp)
            .each([](flecs::entity e, DER::RealPower &pwr, DER::MaxRealPower &limit, DER::Energy &energy)
                  {
                float delta_time = 1.0 / 3600.0; // hours
                pwr.value = limit.value;
                if (energy.value > 0){
                    std::cout << "Remove : " << pwr.value*delta_time << "\n";
                    energy.value -= pwr.value*delta_time;
                    std::cout << energy.value << "\n";
                }
                if (energy.value <= 0){
                    e.add(WaterHeater::State::Shed);
                    pwr.value = 0;
                    std::cout << "Finished" << "\n";
                } });
    }

} // namespace WaterHeater
