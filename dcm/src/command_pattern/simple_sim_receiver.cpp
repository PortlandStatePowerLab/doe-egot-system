#include "include/command_pattern/simple_sim_receiver.hpp"

using namespace dcm;

SimpleSimulatorReceiver::SimpleSimulatorReceiver()
{
    std::cout << " SimpleSimulatorReceiver default constructor " << std::endl;
    sim_der_ = new der::DERSimulator;
}

SimpleSimulatorReceiver::~SimpleSimulatorReceiver()
{
    std::cout << "SimpleSimulatorReceiver Destructor " << std::endl;
    delete sim_der_;
}

std::string SimpleSimulatorReceiver::Import()
{
    std::string response = sim_der_->ImportEnergy();
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string SimpleSimulatorReceiver::Export()
{
    std::string response = sim_der_->ExportEnergy();
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string SimpleSimulatorReceiver::GetEnergy()
{
    std::string response = sim_der_->GetEnergy();
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string SimpleSimulatorReceiver::GetNameplate()
{
    std::string response = sim_der_->GetNameplate();
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string SimpleSimulatorReceiver::Idle()
{
    std::string response = sim_der_->Idle();
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string SimpleSimulatorReceiver::CriticalPeakEvent()
{
    std::cout << "SimpleSimReceiver CriticalPeakEvent, not supported currently" << std::endl;
}

std::string SimpleSimulatorReceiver::GridEmergencyEvent()
{
    std::cout << "SimpleSimReceiver GridEmergencyEvent, not supported currently" << std::endl;
}

void SimpleSimulatorReceiver::IncrementSimulatorProgress()
{
    sim_der_->IncrementProgress();
}