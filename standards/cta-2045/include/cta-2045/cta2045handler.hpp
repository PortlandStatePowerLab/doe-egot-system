# pragma once
#include <cea2045/processmessage/IUCM.h>

struct DeviceInfo{
	unsigned short deviceType;
	unsigned short vendorId;
	unsigned short firmwareYear;
	unsigned short firmwareMonth;
	unsigned short firmwareDay;
};

struct CommodityMessage{
	int commodityCode;
	int cumulativeAmount;
	int instantRate;
};

class CTA2045Handler : public cea2045::IUCM {
    public:
        CTA2045Handler();
        virtual ~CTA2045Handler();
        // --------------------------------- EPRI CTA2045 Reqs ------------------------------ 
        virtual bool isMessageTypeSupported(cea2045::MessageTypeCode messageType);
        virtual cea2045::MaxPayloadLengthCode getMaxPayload();
        virtual void processMaxPayloadResponse(cea2045::MaxPayloadLengthCode maxPayload);
        virtual void processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse* message);
        virtual void processCommodityResponse(cea2045::cea2045CommodityResponse* message);
        virtual void processSetEnergyPriceResponse(cea2045::cea2045IntermediateResponse* message) {};
        virtual void processSetTemperatureOffsetResponse(cea2045::cea2045IntermediateResponse* message) {};
        virtual void processGetTemperatureOffsetResponse(cea2045::cea2045GetTemperateOffsetResponse* message) {};
        virtual void processSetSetpointsResponse(cea2045::cea2045IntermediateResponse* message) {};
        virtual void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse1* message) {};
        virtual void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse2* message) {};
        virtual void processStartCyclingResponse(cea2045::cea2045IntermediateResponse* message) {};
        virtual void processTerminateCyclingResponse(cea2045::cea2045IntermediateResponse* message) {};
        virtual void processGetPresentTemperatureResponse(cea2045::cea2045GetPresentTemperatureResponse* message) {};
        virtual void processGetUTCTimeResponse(cea2045::cea2045GetUTCTimeResponse* message) {};;
        virtual void processAckReceived(cea2045::MessageCode messageCode);
        virtual void processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode messageCode);
        virtual void processAppAckReceived(cea2045::cea2045Basic* message);
        virtual void processAppNakReceived(cea2045::cea2045Basic* message);
        virtual void processOperationalStateReceived(cea2045::cea2045Basic* message);
        virtual void processAppCustomerOverride(cea2045::cea2045Basic* message);
        virtual void processIncompleteMessage(const unsigned char* buffer, unsigned int numBytes);
        // -------------------------------------------------------------------------------------
        
    private:
        cea2045::MaxPayloadLengthCode max_payload_size;
		DeviceInfo device_info;
		CommodityMessage last_commodity_messages;
		int last_energy_take;
};