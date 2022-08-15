#ifndef __TRUST_DER_CLIENT_H__
#define __TRUST_DER_CLIENT_H__

#include <cta2045/abstract_device.hpp>
#include <cta2045/ucm.hpp>
#include <string>
#include <mutex>

class TrustUCM : public UCM
{
public:
    TrustUCM();
    virtual ~TrustUCM();

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
    cta2045::DeviceInfo device_info_;
    cta2045::commodity_map commodities_;
    cea2045::cea2045GetTemperateOffsetResponse temperature_offset_;
    cea2045::cea2045GetSetpointsResponse1 setpoint_1_;
    cea2045::cea2045GetSetpointsResponse2 setpoint_2_;
    cea2045::cea2045GetPresentTemperatureResponse present_temperature_;
    cea2045::cea2045GetUTCTimeResponse utc_time_;
};

class TrustCTADevice : public cta2045::AbstractDevice
{
public:
    TrustCTADevice(const std::string &context);
    ~TrustCTADevice() noexcept;

    cta2045::DeviceInfo getDeviceInfo() override;
    cta2045::commodity_map getCommodity() override;
    cea2045::ResponseCodes loadUp(const uint8_t duration = 0) override;
    cea2045::ResponseCodes shed(const uint8_t duration = 0) override;
    cea2045::ResponseCodes endShed(const uint8_t duration = 0) override;
    cea2045::ResponseCodes criticalPeakEvent(const uint8_t duration = 0) override;
    cea2045::ResponseCodes gridEmergency(const uint8_t duration = 0) override;

private:
    cea2045::ResponseCodes response_codes_;
    cea2045::CEA2045SerialPort *serial_port_;
    TrustUCM *ucm_;
    cea2045::ICEA2045DeviceUCM *device_;
};

class TrustDERClient : public cta2045::AbstractDevice
{
public:
    TrustDERClient(TrustDERClient &other) = delete;         // clonable
    void operator=(const TrustDERClient &) = delete;        // assignable
    static TrustDERClient* getInstance(const std::string& context);
    static TrustDERClient* getInstance();

    cta2045::DeviceInfo getDeviceInfo() override;
    cta2045::commodity_map getCommodity() override;
    cea2045::ResponseCodes loadUp(const uint8_t duration = 0) override;
    cea2045::ResponseCodes shed(const uint8_t duration = 0) override;
    cea2045::ResponseCodes endShed(const uint8_t duration = 0) override;
    cea2045::ResponseCodes criticalPeakEvent(const uint8_t duration = 0) override;
    cea2045::ResponseCodes gridEmergency(const uint8_t duration = 0) override;

protected:
    TrustDERClient(const std::string &context);
    ~TrustDERClient();

private:
    // thread-safe singleton instance
    static TrustDERClient *instance_;
    static std::mutex mutex_;
    TrustCTADevice device_;
};

#endif // __TRUST_DER_CLIENT_H__