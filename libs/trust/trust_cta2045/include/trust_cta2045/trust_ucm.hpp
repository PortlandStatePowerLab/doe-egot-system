#ifndef __TRUST_CTA2045_UCM_H__
#define __TRUST_CTA2045_UCM_H__

#include <string>
#include <unordered_map>
#include <cea2045/processmessage/IUCM.h>

namespace cta2045
{
    using commodity_map = std::unordered_map<uint8_t, cea2045::cea2045CommodityData>;

    enum class Commodity : uint8_t
    {
        kElectricityConsumed,
        kElectricityProduced,
        kNaturalGasCubicFeet,
        kWaterGallons,
        kNaturalGasCubicMeters,
        kWaterLiters,
        kTotalEnergy,
        kPresentEnergy,
        kRatedMaxPowerConsumption,
        kRatedMaxPowerProduction,
        kTotalLoadUp,
        kPresentLoadup
    };

        enum class DeviceType : uint8_t
    {
        kUnspecified,
        kWaterHeaterGas,
        kWaterHeaterElectric,
        kWaterHeaterHeatPump
    }; 

    enum class CapabilityBitMap : uint8_t
    {
        kCycling,
        kTierMode,
        kPriceMode,
        kTemperatureOffset,
        kContinuouslyVariablePower,
        kEfficiencyLevel
    };

    struct DeviceInfo
    {
        uint32_t device_type;
        uint32_t capability_map;
        uint32_t vendor_id;
        uint32_t firmware_year;
        uint32_t firmware_month;
        uint32_t firmware_day;
        uint32_t firmware_major;
        uint32_t firmware_minor;
    };

} // namespace cta2045

namespace trust
{
    class cea2045UCM : public cea2045::IUCM
    {
    public:
        cea2045UCM();
        ~cea2045UCM();

        bool isMessageTypeSupported(cea2045::MessageTypeCode type_code) override;
        cea2045::MaxPayloadLengthCode getMaxPayload();
        void processMaxPayloadResponse(cea2045::MaxPayloadLengthCode payload) override;
        void processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse *message) override;
        void processCommodityResponse(cea2045::cea2045CommodityResponse *message) override;
        void processSetEnergyPriceResponse(cea2045::cea2045IntermediateResponse *message) override;
        void processSetTemperatureOffsetResponse(cea2045::cea2045IntermediateResponse *message) override;
        void processGetTemperatureOffsetResponse(cea2045::cea2045GetTemperateOffsetResponse *message) override;
        void processSetSetpointsResponse(cea2045::cea2045IntermediateResponse *message) override;
        void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse1 *message) override;
        void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse2 *message) override;
        void processStartCyclingResponse(cea2045::cea2045IntermediateResponse *message) override;
        void processTerminateCyclingResponse(cea2045::cea2045IntermediateResponse *message) override;
        void processGetPresentTemperatureResponse(cea2045::cea2045GetPresentTemperatureResponse *message) override;
        void processGetUTCTimeResponse(cea2045::cea2045GetUTCTimeResponse *message) override;
        void processAckReceived(cea2045::MessageCode code) override;
        void processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode code) override;
        void processAppAckReceived(cea2045::cea2045Basic *message) override;
        void processAppNakReceived(cea2045::cea2045Basic *message) override;
        void processOperationalStateReceived(cea2045::cea2045Basic *message) override;
        void processAppCustomerOverride(cea2045::cea2045Basic *message) override;
        void processIncompleteMessage(const unsigned char *buffer, unsigned int byte_count) override;

        cea2045::MaxPayloadLengthCode max_payload_;
        cta2045::DeviceInfo device_info_;
        cta2045::commodity_map commodities_;
        cea2045::cea2045GetTemperateOffsetResponse temperature_offset_;
        cea2045::cea2045GetSetpointsResponse1 setpoint_1_;
        cea2045::cea2045GetSetpointsResponse2 setpoint_2_;
        cea2045::cea2045GetPresentTemperatureResponse present_temperature_;
        cea2045::cea2045GetUTCTimeResponse utc_time_;
    };
} // namespace trust

#endif // __TRUST_CTA2045_UCM_H__
