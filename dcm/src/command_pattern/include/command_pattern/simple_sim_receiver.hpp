#ifndef __SIMPLE_SIM_RECEIVER_H__
#define __SIMPLE_SIM_RECEIVER_H__
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
#include "base_receiver.hpp"

namespace dcm
{/*
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
*/
    // This is a receiver class for interacting with a simulated DER
    class SimpleSimulatorReceiver : public BaseReceiver
    {
    public:
        SimpleSimulatorReceiver();
        ~SimpleSimulatorReceiver();
        std::string Import();
        std::string Export();
        std::string GetEnergy();
        std::string GetNameplate();
        std::string Idle();
        std::string CriticalPeakEvent();
        std::string GridEmergencyEvent();
        void IncrementSimulatorProgress();

    private:
        xml::XMLCommandAdapter xml_writer_;
        der::DERSimulator *sim_der_;
    };

} // namespace dcm

#endif //__SIMPLE_SIM_RECEIVER_H__