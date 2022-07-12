#ifndef ECS_EPRI_UCM_IMPL_H_
#define ECS_EPRI_UCM_IMPL_H_

#include <cea2045/processmessage/IUCM.h>
#include <condition_variable>
#include <mutex>
#include "cta2045_receiver.hpp"

namespace dcm
{

class EPRI_UCM : public cea2045::IUCM
{
private:
	cea2045::MaxPayloadLengthCode m_sgdMaxPayload;
    std::string *comm_log_; //no data structure to simplify/avoid rquirement for memory/clearing old data
    CombinedHttpsClient *combined_client_;
	xml::XMLCommandAdapter xml_writer_;
	cea2045::MSTimer *timer_;

public:
	EPRI_UCM();
    EPRI_UCM(std::string * comm, CombinedHttpsClient *client, cea2045::MSTimer *t);
	virtual ~EPRI_UCM();

	virtual bool isMessageTypeSupported(cea2045::MessageTypeCode messageType);
	virtual cea2045::MaxPayloadLengthCode getMaxPayload();

	virtual void processMaxPayloadResponse(cea2045::MaxPayloadLengthCode maxPayload);
	virtual void processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse *message);
	virtual void processCommodityResponse(cea2045::cea2045CommodityResponse *message);
	virtual void processSetEnergyPriceResponse(cea2045::cea2045IntermediateResponse *message) {};
	virtual void processSetTemperatureOffsetResponse(cea2045::cea2045IntermediateResponse *message) {};
	virtual void processGetTemperatureOffsetResponse(cea2045::cea2045GetTemperateOffsetResponse *message) {};
	virtual void processSetSetpointsResponse(cea2045::cea2045IntermediateResponse *message) {};
	virtual void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse1 *message) {};
	virtual void processGetSetpointsResponse(cea2045::cea2045GetSetpointsResponse2 *message) {};
	virtual void processStartCyclingResponse(cea2045::cea2045IntermediateResponse *message) {};
	virtual void processTerminateCyclingResponse(cea2045::cea2045IntermediateResponse *message) {};
	virtual void processGetPresentTemperatureResponse(cea2045::cea2045GetPresentTemperatureResponse *message) {};
	virtual void processGetUTCTimeResponse(cea2045::cea2045GetUTCTimeResponse *message) {};;
	virtual void processAckReceived(cea2045::MessageCode messageCode);
	virtual void processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode messageCode);

	virtual void processAppAckReceived(cea2045::cea2045Basic *message);
	virtual void processAppNakReceived(cea2045::cea2045Basic *message);
	virtual void processOperationalStateReceived(cea2045::cea2045Basic *message);
	virtual void processAppCustomerOverride(cea2045::cea2045Basic *message);

	virtual void processIncompleteMessage(const unsigned char *buffer, unsigned int numBytes);
};
} //namespace dcm

#endif //ECS_EPRI_UCM_IMPL_H_