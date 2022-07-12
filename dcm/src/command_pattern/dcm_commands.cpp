#include "include/command_pattern/dcm_commands.hpp"

using namespace dcm;

BaseCommand::BaseCommand() : https_client_(nullptr), receiver_(nullptr)
{
    // do nothing
}

BaseCommand::BaseCommand(CombinedHttpsClient *c, BaseReceiver *r)
    : https_client_(c), receiver_(r)
{
    // do nothing
}

BaseCommand::~BaseCommand()
{
    //delete https_client_;
    //delete receiver_;
}

//=================================================================================

ImportEnergy::ImportEnergy()
{
    // do nothing
}

ImportEnergy::ImportEnergy(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    std::cout << "ImportEnergy Command Constructed " << std::endl;
}

ImportEnergy::~ImportEnergy()
{
    // do nothing
}

std::string ImportEnergy::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  ImportEnergy Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "ImportEnergyCommand", "ImportEnergy"));

    response_from_der = receiver_->Import();
    
    //https_client_->Post("DTM", response_from_der);

    //std::cout << "response from DER was: " << response_from_der << std::endl;
    //std::string msg_in =  xml_writer_.ReturnCustomCommand("DCM", "DER", response_from_der, "na", "na", "response");
    //https_client_->Post("DTM",msg_in);

    return response_from_der;
}

//=================================================================================

ExportEnergy::ExportEnergy()
{
    // do nothing
}

ExportEnergy::ExportEnergy(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

ExportEnergy::~ExportEnergy()
{
    // do nothing
}

std::string ExportEnergy::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  ExportEnergy Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "ExportEnergyCommand", "ExportEnergy"));

    response_from_der = receiver_->Export();
    //https_client_->Post("DTM", response_from_der);

    return response_from_der;
}

//=================================================================================

GetEnergy::GetEnergy()
{
    // do nothing
}

GetEnergy::GetEnergy(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

GetEnergy::~GetEnergy()
{
    // do nothing
}

std::string GetEnergy::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  GetEnergy Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "GetEnergyCommand", "GetEnergy"));
    response_from_der = receiver_->GetEnergy();
    if (response_from_der[0] == 'C') //if cta2045receiver
    {
        std::cout << "GetEnergy::Execute() response from der: " << response_from_der << std::endl;
    }
    https_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "GetEnergyResponse", response_from_der));
    return response_from_der;
}

//=================================================================================

GetNameplate::GetNameplate()
{
    // do nothing
}

GetNameplate::GetNameplate(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

GetNameplate::~GetNameplate()
{
    // do nothing
}

std::string GetNameplate::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  GetNameplate Command Executing... " << std::endl;

    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "GetNameplateCommand", "GetNameplate"));
    response_from_der = receiver_->GetNameplate();
    https_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "GetNameplateResponse", response_from_der));

    return response_from_der;
}

//=================================================================================

Idle::Idle()
{
    // do nothing
}

Idle::Idle(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

Idle::~Idle()
{
    // do nothing
}

std::string Idle::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  Idle Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "IdleCommand", "Idle"));

    response_from_der = receiver_->Idle();
    //https_client_->Post("DTM", response_from_der);

    return response_from_der;
}

//=================================================================================

CriticalPeakEvent::CriticalPeakEvent()
{
    // do nothing
}

CriticalPeakEvent::CriticalPeakEvent(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

CriticalPeakEvent::~CriticalPeakEvent()
{
    // do nothing
}

std::string CriticalPeakEvent::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  CriticalPeakEvent Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "CriticalPeakEventCommand", "CriticalPeakEvent"));
    response_from_der = receiver_->CriticalPeakEvent();
    //https_client_->Post("DTM", response_from_der);

    return response_from_der;
}

//=================================================================================

GridEmergencyEvent::GridEmergencyEvent()
{
    // do nothing

}

GridEmergencyEvent::GridEmergencyEvent(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

GridEmergencyEvent::~GridEmergencyEvent()
{
    // do nothing
}
std::string GridEmergencyEvent::Execute()
{
    std::string response_from_der;
    std::cout << "  GridEmergencyEvent Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    https_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "GridEmergencyEventCommand", "GridEmergencyEvent"));
    response_from_der = receiver_->GridEmergencyEvent();
    //https_client_->Post("DTM", response_from_der);

    return response_from_der;
}