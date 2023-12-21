#include <ecs/client/cta2045/commodity.hpp>
#include <trust/cta2045/trust_device.hpp>

namespace ecs {
namespace client {
namespace commodity {
Module::Module(flecs::world &ecs) {
  /* Register module with world */
  ecs.module<Module>();
  ecs.component<cea2045::cea2045CommodityData>();

  /* Register system */
  ecs.system<cea2045::cea2045CommodityData>("EnergyTake")
      .each([&](flecs::entity e, cea2045::cea2045CommodityData &data) {
        std::cout << "cta2045: getting commodity data" << std::endl;
        cta2045::commodity_map commodities =
            trust::cta2045Device::getInstance().getCommodity();
        for (const auto commodity : commodities) {
          std::cout << commodity.first << "\n\t"
                    << commodity.second.commodityCode << "\n\t"
                    << commodity.second.cumulativeAmount << "\n\t"
                    << commodity.second.instantaneousRate << std::endl;
        }
      });
};
} // namespace commodity
} // namespace client
} // namespace ecs
