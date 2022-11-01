#include "include/der.hpp"
#include <cstdlib>
#include <iostream>

namespace DER
{
    Module::Module(flecs::world& ecs)
    {
        ecs.module<Module>();

        ecs.component<RealPower>();
        ecs.component<ReactivePower>();
        ecs.component<MaxRealPower>();
        ecs.component<MaxReactivePower>();
        ecs.component<Energy>();
        ecs.component<MaxEnergy>();

        ecs.observer<RealPower,MaxRealPower>("OnSetRealPower")
            .event(flecs::OnSet)
            .each([](RealPower& pwr, MaxRealPower& limit){
                if (pwr.value > limit.value){
                    pwr.value = limit.value;
                    std::cout << "Too big: " << pwr.value  << std::endl;
                }
                
                if (pwr.value + limit.value < 0){
                    pwr.value = 0 - static_cast<float>(limit.value);
                    std::cout << "Too small: " << pwr.value  << std::endl;
                }
            });

        ecs.observer<ReactivePower,MaxReactivePower>("OnSetReactivePower")
            .event(flecs::OnSet)
            .each([](ReactivePower& pwr, MaxReactivePower& limit){
                if (pwr.value > limit.value){
                    pwr.value = limit.value;
                    std::cout << "Too big: " << pwr.value  << std::endl;
                }
                
                if (pwr.value + limit.value < 0){
                    pwr.value = 0 - static_cast<float>(limit.value);
                    std::cout << "Too small: " << pwr.value  << std::endl;
                }
            });

        ecs.observer<Energy,MaxEnergy>("OnSetEnergy")
            .event(flecs::OnSet)
            .each([](Energy& energy, MaxEnergy& limit){
                if (energy.value > limit.value){
                    energy.value = limit.value;
                    std::cout << "Too big: " << energy.value  << std::endl;
                }
                
                if (energy.value + limit.value < 0){
                    energy.value = 0 - static_cast<float>(limit.value);
                    std::cout << "Too small: " << energy.value  << std::endl;
                }
            });

    }

    
} // namespace DER
