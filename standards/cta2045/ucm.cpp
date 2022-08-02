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
    device_info_ = *message;
}

void UCM::processCommodityResponse(cea2045CommodityResponse *message)
{
    size_t count = message->getCommodityDataCount();
    for (size_t i = 0; i < count; i++)
    {
        cea2045CommodityData *data = message->getCommodityData(i);
        commodities_[cta2045::Commodity(data->commodityCode)] = *data;
    }
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
    // TODO
}
