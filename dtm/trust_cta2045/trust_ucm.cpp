#include "include/cta2045/TrustUCM.hpp"
#include <iostream>
#include <trust_https/singleton_trust_https.hpp>

using namespace cea2045;

TrustUCM::TrustUCM()
{
    max_payload_ = cea2045::MaxPayloadLengthCode::LENGTH2;
}

TrustUCM::~TrustUCM()
{
    // do nothing
}

bool TrustUCM::isMessageTypeSupported(MessageTypeCode type_code)
{
    if (type_code == MessageTypeCode::NONE)
    {
        return false;
    }

    return true;
}

MaxPayloadLengthCode TrustUCM::getMaxPayload()
{
    return max_payload_;
}

void TrustUCM::processMaxPayloadResponse(MaxPayloadLengthCode payload)
{
    max_payload_ = payload;
}

void TrustUCM::processDeviceInfoResponse(cea2045DeviceInfoResponse *message)
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
}

void TrustUCM::processCommodityResponse(cea2045CommodityResponse *message)
{
    size_t count = message->getCommodityDataCount();
    for (size_t i = 0; i < count; i++)
    {
        cea2045CommodityData data = *message->getCommodityData(i);
        commodities_[(uint8_t)data.commodityCode] = data;
    }
}

void TrustUCM::processSetEnergyPriceResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void TrustUCM::processSetTemperatureOffsetResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void TrustUCM::processGetTemperatureOffsetResponse(cea2045GetTemperateOffsetResponse *message)
{
    // TODO
}

void TrustUCM::processSetSetpointsResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void TrustUCM::processGetSetpointsResponse(cea2045GetSetpointsResponse1 *message)
{
    // TODO
}

void TrustUCM::processGetSetpointsResponse(cea2045GetSetpointsResponse2 *message)
{
    // TODO
}

void TrustUCM::processStartCyclingResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void TrustUCM::processTerminateCyclingResponse(cea2045IntermediateResponse *message)
{
    // TODO
}

void TrustUCM::processGetPresentTemperatureResponse(cea2045GetPresentTemperatureResponse *message)
{
    // TODO
}

void TrustUCM::processGetUTCTimeResponse(cea2045GetUTCTimeResponse *message)
{
    // TODO
}

void TrustUCM::processAckReceived(MessageCode code)
{
    // TODO
}

void TrustUCM::processNakReceived(LinkLayerNakCode nak, MessageCode code)
{
    // TODO
}

void TrustUCM::processAppAckReceived(cea2045Basic *message)
{
    // TODO
}

void TrustUCM::processAppNakReceived(cea2045Basic *message)
{
    // TODO
}

void TrustUCM::processOperationalStateReceived(cea2045Basic *message)
{
    // TODO
}

void TrustUCM::processAppCustomerOverride(cea2045Basic *message)
{
    // TODO
}

void TrustUCM::processIncompleteMessage(const unsigned char *buffer, unsigned int byte_count)
{
    std::cout << "CTA2045 processIncompleteMessage\n";
}
