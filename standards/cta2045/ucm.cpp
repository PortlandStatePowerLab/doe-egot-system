#include "include/cta2045/ucm.hpp"
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
    max_payload_ = payload;
}

void UCM::processDeviceInfoResponse(cea2045DeviceInfoResponse *message)
{
    //device_info_ = *message;
    device_info_.device_type = message->getDeviceType();
    device_info_.capability_map = (uint32_t)message->capability;
    device_info_.vendor_id = message->getVendorID();
    device_info_.firmware_day = (uint32_t)message->firmwareDay;
    device_info_.firmware_month = (uint32_t)message->firmwareMonth;
    device_info_.firmware_year = 2000 + (uint32_t)message->firmwareYear20xx;
    device_info_.firmware_minor = (uint32_t)message->firmwareMinor;
    device_info_.firmware_major = (uint32_t)message->firmwareMajor;
}

void UCM::processCommodityResponse(cea2045CommodityResponse *message)
{
    size_t count = message->getCommodityDataCount();
    for (size_t i = 0; i < count; i++)
    {
        cea2045CommodityData data = *message->getCommodityData(i);
        size_t key = (size_t)data.commodityCode;
        std::cout << key << " : cumulative = " << data.getCumulativeAmount() << "\n";
        std::cout << key << " : inst. rate = " << data.getInstantaneousRate() << "\n";
        commodities_[key] = data;
    }
}

void UCM::processSetEnergyPriceResponse(cea2045IntermediateResponse *message)
{
    std::cout << "CTA2045 processSetEnergyPriceResponse\n";
}

void UCM::processSetTemperatureOffsetResponse(cea2045IntermediateResponse *message)
{
    std::cout << "CTA2045 processSetTemperatureOffsetResponse\n";
}

void UCM::processGetTemperatureOffsetResponse(cea2045GetTemperateOffsetResponse *message)
{
    std::cout << "CTA2045 processGetTemperatureOffsetResponse\n";
}

void UCM::processSetSetpointsResponse(cea2045IntermediateResponse *message)
{
    std::cout << "CTA2045 processSetSetpointsResponse\n";
}

void UCM::processGetSetpointsResponse(cea2045GetSetpointsResponse1 *message)
{
    std::cout << "CTA2045 processGetSetpointsResponse\n";
}

void UCM::processGetSetpointsResponse(cea2045GetSetpointsResponse2 *message)
{
    std::cout << "CTA2045 processGetSetpointsResponse\n";
}

void UCM::processStartCyclingResponse(cea2045IntermediateResponse *message)
{
    std::cout << "CTA2045 processStartCyclingResponse\n";
}

void UCM::processTerminateCyclingResponse(cea2045IntermediateResponse *message)
{
    std::cout << "CTA2045 processTerminateCyclingResponse\n";
}

void UCM::processGetPresentTemperatureResponse(cea2045GetPresentTemperatureResponse *message)
{
    std::cout << "CTA2045 processGetPresentTemperatureResponse\n";
}

void UCM::processGetUTCTimeResponse(cea2045GetUTCTimeResponse *message)
{
    std::cout << "CTA2045 processGetUTCTimeResponse\n";
}

void UCM::processAckReceived(MessageCode code)
{
    std::cout << "CTA2045 processAckReceived\n";
}

void UCM::processNakReceived(LinkLayerNakCode nak, MessageCode code)
{
    std::cout << "CTA2045 processNakReceived\n";
}

void UCM::processAppAckReceived(cea2045Basic *message)
{
    std::cout << "CTA2045 processAppAckReceived\n";
}

void UCM::processAppNakReceived(cea2045Basic *message)
{
    std::cout << "CTA2045 processAppNakReceived\n";
}

void UCM::processOperationalStateReceived(cea2045Basic *message)
{
    std::cout << "CTA2045 processOperationalStateReceived\n";
}

void UCM::processAppCustomerOverride(cea2045Basic *message)
{
    std::cout << "CTA2045 processAppCustomerOverride\n";
}

void UCM::processIncompleteMessage(const unsigned char *buffer, unsigned int byte_count)
{
    std::cout << "CTA2045 processIncompleteMessage\n";
}
