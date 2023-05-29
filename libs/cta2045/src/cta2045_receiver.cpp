#include "include/cta2045_receiver/cta2045_receiver.hpp"



namespace dcm
{
using namespace cea2045;
CTA2045Receiver::CTA2045Receiver(CombinedHttpsClient *c) : epri_ucm_(&response_, c, &timer_), serial_port_("/dev/ttyAMA0"), shutdown_(false)
{
    std::cout << "CTA2045 Receiver Default Constructor" << std::endl;
    if (!serial_port_.open())
	{
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
	}
    else
    {
        std::string msg_out = xml_writer_.WriteMsg("DCM", "DER", "CTA2045_Message", "CTA2045_Startup", "Startup... Initiating CTA2045 Communications");
        c->Post("DTM", msg_out);
        device_ = cea2045::DeviceFactory::createUCM(&serial_port_, &epri_ucm_);
        device_->start();
        timer_.reset();
        responseCodes_ = device_->querySuportDataLinkMessages().get();
        LOG(INFO) << "  query data link elapsed time: " << timer_.getElapsedMS();
        timer_.reset();
        responseCodes_ = device_->queryMaxPayload().get();
        LOG(INFO) << "  query max payload elapsed time: " << timer_.getElapsedMS();
        timer_.reset();
        responseCodes_ = device_->querySuportIntermediateMessages().get();
        LOG(INFO) << "  query intermediate elapsed time: " << timer_.getElapsedMS();
        timer_.reset();
        responseCodes_ = device_->intermediateGetDeviceInformation().get();
        LOG(INFO) << "  device info elapsed time: " << timer_.getElapsedMS();
        LOG(INFO) << "startup complete";
        
    }
}

CTA2045Receiver::~CTA2045Receiver() 
{
    std::cout << "cta2045receiver destructor" << std::endl;
    device_->shutDown();
    delete (device_);
}

std::string CTA2045Receiver::Import() 
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver Import() " << std::endl;

    timer_.reset();
    device_->basicLoadUp(0).get();
    elapsed = timer_.getElapsedMS();

    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver Import() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
}

std::string CTA2045Receiver::Export() 
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver Export() " << std::endl;

    timer_.reset();
    device_->basicShed(0).get();
    elapsed = timer_.getElapsedMS();

    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver Expor() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
}

std::string CTA2045Receiver::GetEnergy() 
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver GetEnergy() " << std::endl;

    timer_.reset();
    device_->intermediateGetCommodity().get();
    elapsed = timer_.getElapsedMS();

    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver getenergy() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
}

std::string CTA2045Receiver::GetNameplate() 
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver GetNameplate() " << std::endl;

    timer_.reset();
    device_->intermediateGetDeviceInformation().get();
    elapsed = timer_.getElapsedMS();
    
    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver::getNamePlate GetNameplate() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
    //return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string CTA2045Receiver::Idle() 
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver Idle() " << std::endl;

    timer_.reset();
    device_->basicEndShed(0).get();
    elapsed = timer_.getElapsedMS();

    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver Idle() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
}

std::string CTA2045Receiver::CriticalPeakEvent()
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver CriticalPeak() " << std::endl;

    timer_.reset();
    device_->basicCriticalPeakEvent(0).get();
    elapsed = timer_.getElapsedMS();

    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver criticalPeak() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
}

std::string CTA2045Receiver::GridEmergencyEvent()
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver GridEmergencyEvent() " << std::endl;

    timer_.reset();
    device_->basicGridEmergency(0).get();
    elapsed = timer_.getElapsedMS();

    log = "CTA2045: " + response_; //for command
    response_.erase();
    std::cout << " cta2045receiver GridEmergencyEvent() log: " << log << std::endl;

    return log + ", elapsed: " + std::to_string(elapsed);
}

} // namespace dcm

