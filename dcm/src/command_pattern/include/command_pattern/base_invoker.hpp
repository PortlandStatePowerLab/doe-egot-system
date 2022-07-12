#ifndef __BASE_INVOKER_H__
#define __BASE_INVOKER_H__
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

namespace dcm
{

class BaseInvoker
{
    public:
        BaseInvoker(
            flecs::world *shared,
            ImportEnergy *imp,
            ExportEnergy *exp,
            GetEnergy *get_e,
            GetNameplate *get_n,
            Idle *idle,
            CriticalPeakEvent *crit);
        ~BaseInvoker();
        virtual void ProcessResource(flecs::entity *e) = 0;

    protected:
        flecs::world *shared_world_ptr_;
        ImportEnergy *import_;
        ExportEnergy *export_;
        GetEnergy *get_energy_;
        GetNameplate *get_nameplate_;
        Idle *idle_;
        CriticalPeakEvent *crit_;
};

} //namespace dcm
#endif //__S_SIM_INVOKER_H__