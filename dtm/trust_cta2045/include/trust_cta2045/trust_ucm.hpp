#ifndef __TRUST_CTA2045_UCM_H__
#define __TRUST_CTA2045_UCM_H__

#include <string>
#include <unordered_map>
#include <cta2045/ucm.hpp>

class TrustUCM : public UCM
{
public:
    TrustUCM();
    ~TrustUCM();

    bool isMessageTypeSupported(cea2045::MessageTypeCode type_code);
    cea2045::MaxPayloadLengthCode getMaxPayload();
    void processMaxPayloadResponse(cea2045::MaxPayloadLengthCode payload);
    void processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse *message);
    void processCommodityResponse(cea2045::cea2045CommodityResponse *message);
    void processSetEnergyPriceResponse(cea2045::cea2045IntermediateResponse *message);
    void processSetTemperatureOffsetResponse(cea2045::cea2045IntermediateResponse *message);
    void processGetTemperatureOffsetResponse(cea2045::cea2045GetTemperateOffsetResponse *message);
    void processSetSetpointsResponse(cea2045::cea2045IntermediateResponse *message);
    void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse1 *message);
    void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse2 *message);
    void processStartCyclingResponse(cea2045::cea2045IntermediateResponse *message);
    void processTerminateCyclingResponse(cea2045::cea2045IntermediateResponse *message);
    void processGetPresentTemperatureResponse(cea2045::cea2045GetPresentTemperatureResponse *message);
    void processGetUTCTimeResponse(cea2045::cea2045GetUTCTimeResponse *message);
    void processAckReceived(cea2045::MessageCode code);
    void processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode code);
    void processAppAckReceived(cea2045::cea2045Basic *message);
    void processAppNakReceived(cea2045::cea2045Basic *message);
    void processOperationalStateReceived(cea2045::cea2045Basic *message);
    void processAppCustomerOverride(cea2045::cea2045Basic *message);
    void processIncompleteMessage(const unsigned char *buffer, unsigned int byte_count);
};               

#endif // __TRUST_CTA2045_UCM_H__
