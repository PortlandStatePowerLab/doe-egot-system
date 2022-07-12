#ifndef __CTA2045_RECEIVER_H__
#define __CTA2045_RECEIVER_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <cea2045/processmessage/IUCM.h>
#include <command_pattern/base_receiver.hpp>
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/util/MSTimer.h>
#include "ecs_epri_ucm_impl.hpp"
#include "easylogging++.h"


namespace dcm
{

// This is a receiver class for interacting with a simulated DER
class CTA2045Receiver : public BaseReceiver
{
    public:

        CTA2045Receiver(CombinedHttpsClient *c);
        ~CTA2045Receiver();
        std::string Import(); 
        std::string Export(); 
        std::string GetEnergy(); 
        std::string GetNameplate(); 
        std::string Idle(); 
        std::string CriticalPeakEvent();
        std::string GridEmergencyEvent();

    private:
        std::string response_;
        xml::XMLCommandAdapter xml_writer_;
        //UCMImpl epri_ucm_;
        dcm::EPRI_UCM epri_ucm_;
        cea2045::CEA2045SerialPort serial_port_;
        cea2045::ResponseCodes responseCodes_;
        cea2045::MSTimer timer_;
        bool shutdown_;
        cea2045::ICEA2045DeviceUCM * device_;
};

} // namespace dcm


#endif //__ECS_DCM_H__