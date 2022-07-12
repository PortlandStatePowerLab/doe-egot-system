#ifndef __BASE_RECEIVER_H__
#define __BASE_RECEIVER_H__
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
#include <ecs/der_simulator.hpp>
#include <dtm_msg_writer/announce_xml.h>

namespace dcm
{
    // abstract class
    class BaseReceiver
    {
    public:
        virtual std::string Import() = 0;
        virtual std::string Export() = 0;
        virtual std::string GetEnergy() = 0;
        virtual std::string GetNameplate() = 0;
        virtual std::string Idle() = 0;
        virtual std::string CriticalPeakEvent() = 0;
        virtual std::string GridEmergencyEvent() = 0;

    private:
    };

} // namespace dcm

#endif //__SIMPLE_SIM_RECEIVER_H__