#include "include/sep/fsa.hpp"
#include "include/sep/simple_types.hpp"

namespace sep {
namespace fsab {

Module::Module(flecs::world& world){
    world.module<Module>();

    world.component<CustomerAccountListLink>();
    world.component<DemandResponseProgramListLink>();
    world.component<DERProgramListLink>();
    world.component<FileListLink>();
    world.component<MessagingProgramListLink>();
    world.component<PrepaymentListLink>();
    world.component<ResponseSetListLink>();
    world.component<TariffProfileListLink>();
    world.component<UsagePointListLink>();

    // world.prefab<FunctionSetAssignmentsBase>();
    // world.prefab<CustomerAccountListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<DemandResponseProgramListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<DERProgramListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<FileListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<MessagingProgramListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<PrepaymentListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<ResponseSetListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<TariffProfileListLink>().slot_of<FunctionSetAssignmentsBase>();
    // world.prefab<UsagePointListLink>().slot_of<FunctionSetAssignmentsBase>();
};

} // namespace fsab
} // namespace sep