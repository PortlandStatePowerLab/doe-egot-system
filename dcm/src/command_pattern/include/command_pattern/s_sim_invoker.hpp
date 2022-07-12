#ifndef __S_SIM_INVOKER_H__
#define __S_SIM_INVOKER_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include <sstream>
#include <https/https_client.hpp>
#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ecs/sim_invoker_module.hpp>
#include <ecs/dcm_components_module.hpp>
#include "dcm_commands.hpp"
#include "base_invoker.hpp"

namespace dcm
{
class SimpleSimulatorFlowResInvoker : public BaseInvoker
{
    public:
        SimpleSimulatorFlowResInvoker(
            flecs::world *shared,
            ImportEnergy *imp,
            ExportEnergy *exp,
            GetEnergy *get_e,
            GetNameplate *get_n,
            Idle *idle,
            CriticalPeakEvent *crit);
        ~SimpleSimulatorFlowResInvoker();
        void ProcessResource(flecs::entity *e);

    private:
};   

} //namespace dcm
#endif //__S_SIM_INVOKER_H__