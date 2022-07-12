#ifndef __DCM_COMMANDS_H__
#define __DCM_COMMANDS_H__

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
#include "simple_sim_receiver.hpp"
#include <dtm_msg_writer/announce_xml.h>

namespace dcm
{

class BaseCommand
{
    public:
        BaseCommand();
        BaseCommand(CombinedHttpsClient *c, BaseReceiver *r);
        ~BaseCommand();
        virtual std::string Execute() = 0;

    protected:
        CombinedHttpsClient *https_client_;
        BaseReceiver *receiver_;
        xml::XMLCommandAdapter xml_writer_;
};

//===============================================================================

class ImportEnergy : public BaseCommand
{
    public:
        ImportEnergy();
        ImportEnergy(CombinedHttpsClient *client, BaseReceiver *receiver);
        ~ImportEnergy();
        std::string Execute();

    private:
};

//===============================================================================

class ExportEnergy : public BaseCommand
{
    public:
        ExportEnergy();
        ExportEnergy(CombinedHttpsClient *client, BaseReceiver *receiver); 
        ~ExportEnergy();
        std::string Execute();

    private:
};

//===============================================================================

class GetEnergy : public BaseCommand
{
    public:
        GetEnergy();
        GetEnergy(CombinedHttpsClient *client, BaseReceiver *receiver);
        ~GetEnergy();
        std::string Execute();

    private:
};

//===============================================================================

class GetNameplate : public BaseCommand
{
    public:
        GetNameplate();
        GetNameplate(CombinedHttpsClient *client, BaseReceiver *receiver);
        ~GetNameplate();
        std::string Execute();

    private:
};

//===============================================================================

class Idle : public BaseCommand
{
    public:
        Idle();
        Idle(CombinedHttpsClient *client, BaseReceiver *receiver);
        ~Idle();
        std::string Execute();

    private:
};

//===============================================================================

class CriticalPeakEvent : public BaseCommand
{
    public:
        CriticalPeakEvent();
        CriticalPeakEvent(CombinedHttpsClient *client, BaseReceiver *receiver);
        ~CriticalPeakEvent();
        std::string Execute();

    private:
};

class GridEmergencyEvent : public BaseCommand
{
    public:
        GridEmergencyEvent();
        GridEmergencyEvent(CombinedHttpsClient *client, BaseReceiver *receiver);
        ~GridEmergencyEvent();
        std::string Execute();

    private:
};

} // namespace dcm

#endif //__DCM_COMMANDS_H__