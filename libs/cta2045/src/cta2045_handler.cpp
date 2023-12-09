#include <cta2045/cta2045handler.hpp>

#include <cea2045/util/MSTimer.h>

#include <chrono>

using namespace std;

CTA2045Handler::CTA2045Handler()
{
	max_payload_size = cea2045::MaxPayloadLengthCode::LENGTH2;
}

//======================================================================================

CTA2045Handler::~CTA2045Handler()
{
	// nothing
}

//======================================================================================

bool CTA2045Handler::isMessageTypeSupported(cea2045::MessageTypeCode messageType)
{
	if (messageType == cea2045::MessageTypeCode::NONE)
		return false;

	return true;
}

//======================================================================================

cea2045::MaxPayloadLengthCode CTA2045Handler::getMaxPayload()
{
	return cea2045::MaxPayloadLengthCode::LENGTH4096;
}

//======================================================================================

void CTA2045Handler::processMaxPayloadResponse(cea2045::MaxPayloadLengthCode maxPayload)
{
	max_payload_size = maxPayload;
}

//======================================================================================

void CTA2045Handler::processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse* message)
{
	// @TODO: copy device info
	device_info.deviceType = message->getDeviceType();
	device_info.vendorId = message->getVendorID();
	
	// @TODO: copy firmawre info into member var
	device_info.firmwareDay = (int)message->firmwareDay;
	device_info.firmwareMonth = (int)message->firmwareMonth;
	device_info.firmwareYear = 2000+(int)message->firmwareYear20xx;
}

//======================================================================================

void CTA2045Handler::processCommodityResponse(cea2045::cea2045CommodityResponse* message)
{
	// LOG(INFO) << "commodity response received.  count: " << message->getCommodityDataCount();

	int count = message->getCommodityDataCount();

	for (int x = 0; x < count; x++)
	{
		cea2045::cea2045CommodityData* data = message->getCommodityData(x);

		// LOG(INFO) << "commodity data: " << x;

		// LOG(INFO) << "        code: " << (int)data->commodityCode;
		// LOG(INFO) << "  cumulative: " << data->getCumulativeAmount();
		// LOG(INFO) << "   inst rate: " << data->getInstantaneousRate();
	}
}

//======================================================================================

void CTA2045Handler::processAckReceived(cea2045::MessageCode messageCode)
{
	// LOG(INFO) << "ack received: " << (int)messageCode;

	switch (messageCode)
	{

	case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
		// LOG(INFO) << "supports data link messages";
		break;

	case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
		// LOG(INFO) << "supports intermediate messages";
		break;

	default:
		break;
	}
}

//======================================================================================

void CTA2045Handler::processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode messageCode)
{
	// LOG(WARNING) << "nak received";

	if (nak == cea2045::LinkLayerNakCode::UNSUPPORTED_MESSAGE_TYPE)
	{
		switch (messageCode)
		{

		case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
			// LOG(WARNING) << "does not support data link";
			break;

		case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
			// LOG(WARNING) << "does not support intermediate";
			break;

		default:
			break;
		}
	}
}

//======================================================================================

void CTA2045Handler::processOperationalStateReceived(cea2045::cea2045Basic* message)
{
	// LOG(INFO) << "operational state received " << (int)message->opCode2;
}

//======================================================================================

void CTA2045Handler::processAppAckReceived(cea2045::cea2045Basic* message)
{
	// LOG(INFO) << "app ack received";
}

//======================================================================================

void CTA2045Handler::processAppNakReceived(cea2045::cea2045Basic* message)
{
	// LOG(INFO) << "app nak received";
}

//======================================================================================

void CTA2045Handler::processAppCustomerOverride(cea2045::cea2045Basic* message)
{
	// LOG(INFO) << "app cust override received: " << (int)message->opCode2;
}

//======================================================================================

void CTA2045Handler::processIncompleteMessage(const unsigned char* buffer, unsigned int numBytes)
{
	// LOG(WARNING) << "incomplete message received: " << numBytes;
}