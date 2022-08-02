#ifndef __CTA2045_UCM_H__
#define __CTA2045_UCM_H__

#include <string>
#include <unordered_map>
#include <cea2045/processmessage/IUCM.h>

namespace cta2045
{
    enum class Commodity : uint8_t
    {
        kElectricityConsumed,
        kElectricityProduced,
        kNaturalGas,
        kWaterGallons,
        kNaturalGasLiters,
        kTotalEnergy,
        kPresentEnergy,
        kRatedMaxPowerConsumption,
        kRatedMaxPowerProduction,
        kTotalLoadUp,
        kPresentLoadup
    };
} // namespace cta2045

class UCM : public cea2045::IUCM
{
public:
    UCM();
    virtual ~UCM();

    virtual bool isMessageTypeSupported(cea2045::MessageTypeCode type_code);
    virtual cea2045::MaxPayloadLengthCode getMaxPayload();
    virtual void processMaxPayloadResponse(cea2045::MaxPayloadLengthCode payload);
    virtual void processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse *message);
    virtual void processCommodityResponse(cea2045::cea2045CommodityResponse *message);
    virtual void processSetEnergyPriceResponse(cea2045::cea2045IntermediateResponse *message);
    virtual void processSetTemperatureOffsetResponse(cea2045::cea2045IntermediateResponse *message);
    virtual void processGetTemperatureOffsetResponse(cea2045::cea2045GetTemperateOffsetResponse *message);
    virtual void processSetSetpointsResponse(cea2045::cea2045IntermediateResponse *message);
    virtual void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse1 *message);
    virtual void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse2 *message);
    virtual void processStartCyclingResponse(cea2045::cea2045IntermediateResponse *message);
    virtual void processTerminateCyclingResponse(cea2045::cea2045IntermediateResponse *message);
    virtual void processGetPresentTemperatureResponse(cea2045::cea2045GetPresentTemperatureResponse *message);
    virtual void processGetUTCTimeResponse(cea2045::cea2045GetUTCTimeResponse *message);
    virtual void processAckReceived(cea2045::MessageCode code);
    virtual void processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode code);
    virtual void processAppAckReceived(cea2045::cea2045Basic *message);
    virtual void processAppNakReceived(cea2045::cea2045Basic *message);
    virtual void processOperationalStateReceived(cea2045::cea2045Basic *message);
    virtual void processAppCustomerOverride(cea2045::cea2045Basic *message);
    virtual void processIncompleteMessage(const unsigned char *buffer, unsigned int byte_count);

    cea2045::MaxPayloadLengthCode max_payload_;
    cea2045::cea2045DeviceInfoResponse device_info_;
    std::unordered_map<cta2045::Commodity, cea2045::cea2045CommodityData> commodities_;
    cea2045::cea2045GetTemperateOffsetResponse temperature_offset_;
    cea2045::cea2045GetSetpointsResponse1 setpoint_1_;
    cea2045::cea2045GetSetpointsResponse2 setpoint_2_;
    cea2045::cea2045GetPresentTemperatureResponse present_temperature_;
    cea2045::cea2045GetUTCTimeResponse utc_time_;
};               

#endif // __CTA2045_UCM_H__
