#include <ecs/client/cta2045/commodity.hpp>
#include <sep/models/active_power.hpp>
#include <sep/models/real_energy.hpp>
#include <trust/cta2045/trust_device.hpp>

namespace ecs {
namespace client {
namespace commodity {
Module::Module(flecs::world &ecs) {
  /* Register module with world */
  ecs.module<Module>();
  ecs.component<sep::ActivePower>();
  ecs.component<sep::RealEnergy>();

  /* Register system */
  ecs.system<sep::ActivePower, sep::RealEnergy>("waterheater-metrics")
      .each([](flecs::entity e, sep::ActivePower &w, sep::RealEnergy &wh) {
        std::cout << "cta2045: getting commodity data" << std::endl;
        cta2045::commodity_map commodities =
            trust::cta2045Device::getInstance().getCommodity();
        for (const auto commodity : commodities) {
          if (commodity.first == cta2045::Commodity::kElectricityConsumed) {
            if (w.value != commodity.second.instantaneous) {
              e.set<sep::ActivePower>(
                  {1, static_cast<sep::Int16>(commodity.second.instantaneous)});
            }
          }
          if (commodity.first == cta2045::Commodity::kTotalEnergy) {
            if (wh.value != commodity.second.cummulative) {
              e.set<sep::RealEnergy>(
                  {1, static_cast<sep::UInt48>(commodity.second.cummulative)});
            }
          }
        }
      });

  ecs.observer<sep::ActivePower>("power-logging")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::ActivePower &w) {
        std::cout << "Active Power : " << w.value << std::endl;
      });

  ecs.observer<sep::RealEnergy>("energy-request")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::RealEnergy &wh) {
        if (wh.value >= 2300) {
          std::cout << "Sending FlowReservationRequest" << std::endl;
        } else {
          std::cout << "Energy : " << wh.value << " is less than 2300 threshold"
                    << std::endl;
        }
      });
};
} // namespace commodity
} // namespace client
} // namespace ecs
