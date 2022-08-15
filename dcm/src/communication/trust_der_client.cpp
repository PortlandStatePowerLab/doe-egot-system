#include "include/trust_der_client.hpp"
#include "include/dtm_client.hpp"
#include <trust_xml/trust_xml.hpp>
#include <utilities/utilities.hpp>
#include <iostream>

using namespace cea2045;

UCM::UCM()
{
    max_payload_ = cea2045::MaxPayloadLengthCode::LENGTH2;
}

UCM::~UCM()
{
    // do nothing
}

bool UCM::isMessageTypeSupported(MessageTypeCode type_code)
{
    if (type_code == MessageTypeCode::NONE)
    {
        return false;
    }

    return true;
}

MaxPayloadLengthCode UCM::getMaxPayload()
{
    return max_payload_;
}

void UCM::processMaxPayloadResponse(MaxPayloadLengthCode payload)
{
    dtm::Message msg;
    msg.from = "DER";
    msg.to = "DCM";
    msg.command = "processMaxPayloadResponse";
    msg.args["MaxPayloadLengthCode"] = std::to_string((int)payload);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    max_payload_ = payload;
}

void UCM::processDeviceInfoResponse(cea2045DeviceInfoResponse *message)
{
    //device_info_ = *message;
    device_info_.device_type = message->getDeviceType();
    device_info_.capability_map = (uint64_t)message->capability;
    device_info_.vendor_id = message->getVendorID();
    device_info_.firmware_day = (uint32_t)message->firmwareDay;
    device_info_.firmware_month = (uint32_t)message->firmwareMonth;
    device_info_.firmware_year = 2000 + (uint32_t)message->firmwareYear20xx;
    device_info_.firmware_minor = (uint32_t)message->firmwareMinor;
    device_info_.firmware_major = (uint32_t)message->firmwareMajor;

    dtm::Message msg;
    msg.from = "DER";
    msg.to = "DCM";
    msg.command = "processDeviceInfoResponse";
    msg.args["device type"] = std::to_string(device_info_.device_type);
    msg.args["capability"] = std::to_string(device_info_.capability_map);
    msg.args["vendor id"] = std::to_string(device_info_.vendor_id);
    msg.args["firmware day"] = std::to_string(device_info_.firmware_day);
    msg.args["firmware month"] = std::to_string(device_info_.firmware_month);
    msg.args["firmware year"] = std::to_string(device_info_.firmware_year);
    msg.args["firmware minor"] = std::to_string(device_info_.firmware_minor);
    msg.args["firmware major"] = std::to_string(device_info_.firmware_major);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));
}

void UCM::processCommodityResponse(cea2045CommodityResponse *message)
{    
    dtm::Message msg;
    msg.from = "DER";
    msg.to = "DCM";
    msg.command = "processCommodityResponse";
    msg.timestamp = psu::utilities::getTime();

    size_t count = message->getCommodityDataCount();
    for (size_t i = 0; i < count; i++)
    {
        cea2045CommodityData data = *message->getCommodityData(i);
        std::string code = std::to_string((uint8_t)data.commodityCode);
        commodities_[(uint8_t)data.commodityCode] = data;
        msg.args[code + " : code"] = code;
        msg.args[code + " : cumulative amount"] = std::to_string(data.getCumulativeAmount());
        msg.args[code + " : instantaneous rate"] = std::to_string(data.getInstantaneousRate());
    }

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));
}

void UCM::processSetEnergyPriceResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void UCM::processSetTemperatureOffsetResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void UCM::processGetTemperatureOffsetResponse(cea2045GetTemperateOffsetResponse *message)
{
    // TODO
}

void UCM::processSetSetpointsResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void UCM::processGetSetpointsResponse(cea2045GetSetpointsResponse1 *message)
{
    // TODO
}

void UCM::processGetSetpointsResponse(cea2045GetSetpointsResponse2 *message)
{
    // TODO
}

void UCM::processStartCyclingResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void UCM::processTerminateCyclingResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void UCM::processGetPresentTemperatureResponse(cea2045GetPresentTemperatureResponse *message)
{
    // TODO
}

void UCM::processGetUTCTimeResponse(cea2045GetUTCTimeResponse *message)
{
    // TODO
}

void UCM::processAckReceived(MessageCode code)
{
    // TODO
}

void UCM::processNakReceived(LinkLayerNakCode nak, MessageCode code)
{
    // TODO
}

void UCM::processAppAckReceived(cea2045Basic *message)
{
    // TODO
}

void UCM::processAppNakReceived(cea2045Basic *message)
{
    // TODO
}

void UCM::processOperationalStateReceived(cea2045Basic *message)
{
    // TODO
}

void UCM::processAppCustomerOverride(cea2045Basic *message)
{
    // TODO
}

void UCM::processIncompleteMessage(const unsigned char *buffer, unsigned int byte_count)
{
    dtm::Message msg;
    msg.from = "DER";
    msg.to = "DCM";
    msg.command = "processIncompleteMessage";
    msg.args["buffer"] = std::to_string(*buffer);
    msg.args["byte_count"] = std::to_string(byte_count);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    std::cout << "CTA2045 UCM : incomplete message received. Byte count = " << byte_count << "\n";
}

TrustCTADevice::TrustCTADevice(const std::string &context)
{
    serial_port_ = new CEA2045SerialPort(context);
    if (!serial_port_->open())
    {
        std::cout << "CTA2045 UCM: failed to open serial port\n";
        abort();
    }
    
    ucm_ = new TrustUCM();
    device_ = DeviceFactory::createUCM(serial_port_, ucm_);

    device_->start();

    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "querySuportDataLinkMessages";
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->querySuportDataLinkMessages().get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout
            << "CTA2045 TrustCTADevice: does not support data link messages with code = "
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }

    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "querySuportIntermediateMessages";
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->querySuportIntermediateMessages().get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout
            << "CTA2045 TrustCTADevice: does not support intermediate messages with code = "
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
}

TrustCTADevice::~TrustCTADevice()
{
    device_->shutDown();
    delete device_;
    delete ucm_;
    delete serial_port_;
}

cta2045::DeviceInfo TrustCTADevice::getDeviceInfo()
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "intermediateGetDeviceInformation";
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->intermediateGetDeviceInformation().get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support device info messages with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return ucm_->device_info_;
}

cta2045::commodity_map TrustCTADevice::getCommodity()
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "intermediateGetCommodity";
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->intermediateGetCommodity().get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support get commodity with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return ucm_->commodities_;
}

cea2045::ResponseCodes TrustCTADevice::loadUp(const uint8_t duration)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "basicLoadUp";
    msg.args["duration"] = std::to_string(duration);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->basicLoadUp(duration).get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support loadUp with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return response_codes_;
}

cea2045::ResponseCodes TrustCTADevice::shed(const uint8_t duration)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "basicLoadUp";
    msg.args["duration"] = std::to_string(duration);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->basicShed(duration).get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support shed with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return response_codes_;
}

cea2045::ResponseCodes TrustCTADevice::endShed(const uint8_t duration)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "basicEndShed";
    msg.args["duration"] = std::to_string(duration);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->basicEndShed(duration).get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support endShed with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return response_codes_;
}

cea2045::ResponseCodes TrustCTADevice::criticalPeakEvent(const uint8_t duration)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "basicCriticalPeakEvent";
    msg.args["duration"] = std::to_string(duration);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->basicCriticalPeakEvent(duration).get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support criticalPeakEvent with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return response_codes_;
}

cea2045::ResponseCodes TrustCTADevice::gridEmergency(const uint8_t duration)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "DER";
    msg.command = "basicGridEmergency";
    msg.args["duration"] = std::to_string(duration);
    msg.timestamp = psu::utilities::getTime();

    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    response_codes_ = device_->basicGridEmergency(duration).get();
    if (response_codes_.responesCode != ResponseCode::OK)
    {
        std::cout 
            << "CTA2045 TrustCTADevice: does not support gridEmergency with code = " 
            << static_cast<int>(response_codes_.responesCode);
        abort();
    }
    return response_codes_;
}