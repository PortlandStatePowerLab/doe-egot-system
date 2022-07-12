#include <chrono>
#include <cea2045/util/MSTimer.h>
#include <command_pattern/ecs_dcm.hpp>
#include "include/cta2045_receiver/easylogging++.h"

namespace dcm
{
using namespace std;

EPRI_UCM::EPRI_UCM() : comm_log_(nullptr), combined_client_(nullptr), timer_(nullptr)
{
	m_sgdMaxPayload = cea2045::MaxPayloadLengthCode::LENGTH2;
}

//======================================================================================

EPRI_UCM::EPRI_UCM(std::string * comm, CombinedHttpsClient *client, cea2045::MSTimer *t) 
	: comm_log_(comm), combined_client_(client), timer_(t)
{
	m_sgdMaxPayload = cea2045::MaxPayloadLengthCode::LENGTH2;
}

//======================================================================================

EPRI_UCM::~EPRI_UCM()
{
    if (comm_log_)
        delete comm_log_;
}

//======================================================================================

bool EPRI_UCM::isMessageTypeSupported(cea2045::MessageTypeCode messageType)
{
	//LOG(INFO) << "message type supported received: " << (int)messageType;
	//combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM","CTA2045_Message", "MsgTypeSupportedRcvd", "message type supported received: " + std::to_string((int)messageType) + ", elapsed: " + std::to_string(timer_->getElapsedMS())));

	if (messageType == cea2045::MessageTypeCode::NONE)
		return false;
	
	return true;
}

//======================================================================================

cea2045::MaxPayloadLengthCode EPRI_UCM::getMaxPayload()
{
	LOG(INFO) << "max payload request received";
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "MaxPayloadRequest", "max payload request received, elapsed: " + std::to_string(timer_->getElapsedMS())));
	return cea2045::MaxPayloadLengthCode::LENGTH4096;
}

//======================================================================================

void EPRI_UCM::processMaxPayloadResponse(cea2045::MaxPayloadLengthCode maxPayload)
{
	LOG(INFO) << "max payload response received";
	m_sgdMaxPayload = maxPayload;
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "MaxPayloadResponse", "max payload response received, elapsed: " + std::to_string(timer_->getElapsedMS())));
}

//======================================================================================
/*
	The reason that processDeviceInfoResponse and processCommodityResponse aren't 
	communicating with the DTM directly the way that the other processing methods are
	is that the DCM needs to access the information returned in the body of these responses 
	directly in order to update the GSP and implement control.
*/
void EPRI_UCM::processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse* message)
{
    int yr, mnth, day;
    std::string sep = "-";
    std::string temp = " ";

	LOG(INFO) << "device info response received";

	LOG(INFO) << "    device type: " << message->getDeviceType();
	LOG(INFO) << "      vendor ID: " << message->getVendorID();

	LOG(INFO) << "  firmware date: "
			<< 2000 + (int)message->firmwareYear20xx << "-" << (int)message->firmwareMonth << "-" << (int)message->firmwareDay;

    temp += "device type: " + std::to_string((int)message->getDeviceType());
    temp += ", vendor ID: " + std::to_string((int)message->getVendorID());
    yr = 2000 + (int)message->firmwareYear20xx;
    mnth = (int)message->firmwareMonth;
    day = (int)message->firmwareDay;
    temp += ", firmware date: " + std::to_string(yr) + sep + std::to_string(mnth) + sep + std::to_string(day);
    std::cout << "EPRI_UCM::processDeviceInfoResponse COMM LOG: " << temp << std::endl;
    *comm_log_ = temp; //this saves temp to a shared string so that the calling command class can access the contents
}

//======================================================================================

void EPRI_UCM::processCommodityResponse(cea2045::cea2045CommodityResponse* message)
{
    int code, cumltv, rate;
    std::string temp = " ";
	LOG(INFO) << "commodity response received.  count: " << message->getCommodityDataCount();

	int count = message->getCommodityDataCount();
	for (int x = 0; x < count; x++)
	{
		std::cout << "Commodity Response loop x: " << x << std::endl;
		cea2045::cea2045CommodityData *data = message->getCommodityData(x);

		LOG(INFO) << "commodity data: " << x;

        code = (int)data->commodityCode;
        cumltv = data->getCumulativeAmount();
        rate = data->getInstantaneousRate();

        temp += " commodity code: " + std::to_string(code) + ", cumulative amount: " + std::to_string(cumltv) + ", instantaneous rate: " + std::to_string(rate);
	}
    std::cout << "EPRI_UCM::processCommodityResponse COMMODITY RESPONSE: " << temp << std::endl;
    *comm_log_ = temp; //this saves temp to a shared string so that the calling command class can access the contents
}

//======================================================================================

void EPRI_UCM::processAckReceived(cea2045::MessageCode messageCode)
{
	std::string body, outgoing;
	LOG(INFO) << "ack received: " << (int)messageCode;
	body += "ack received: " + std::to_string((int)messageCode);

	switch (messageCode)
	{

	case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
		LOG(INFO) << "supports data link messages";
		body += ", supports data link messages";
		break;

	case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
		LOG(INFO) << "supports intermediate messages";
		body += ", supports intermediate messages";
		break;

	default:
		break;
	}
	body += ", elapsed: " + std::to_string(timer_->getElapsedMS());
	outgoing = xml_writer_.WriteMsg("DER", "DCM","CTA2045_Message", "AckReceived", body);
	std::cout << "about to POST from processAckReceived" << std::endl;
	combined_client_->Post("DTM", outgoing);
}

//======================================================================================

void EPRI_UCM::processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode messageCode)
{
	std::string body, outgoing;
	LOG(WARNING) << "nak received";
	body += "nak received: ";

	if (nak == cea2045::LinkLayerNakCode::UNSUPPORTED_MESSAGE_TYPE)
	{
		switch (messageCode)
		{

		case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
			LOG(WARNING) << "does not support data link";
			body += "does not support data link";
			break;

		case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
			LOG(WARNING) << "does not support intermediate";
			body += "does not support intermediate";
			break;

		default:
			break;
		}
	}
	body += ", elapsed: " + std::to_string(timer_->getElapsedMS());
	outgoing = xml_writer_.WriteMsg("DER", "DCM","CTA2045_Message", "NakReceived", body);
	std::cout << "about to POST from processNakReceived" << std::endl;
	combined_client_->Post("DTM", outgoing);
}

//======================================================================================

void EPRI_UCM::processOperationalStateReceived(cea2045::cea2045Basic *message)
{
	LOG(INFO) << "operational state received " << (int)message->opCode2;
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "OpStateReceived", std::to_string((int)message->opCode2) + ", elapsed: " + std::to_string(timer_->getElapsedMS())));
}

//======================================================================================

void EPRI_UCM::processAppAckReceived(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app ack received";
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "AppAck", "app ack received, elapsed: " + std::to_string(timer_->getElapsedMS())));
}

//======================================================================================

void EPRI_UCM::processAppNakReceived(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app nak received";
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "AppNak", "app nak received, elapsed: " + std::to_string(timer_->getElapsedMS())));
}

//======================================================================================

void EPRI_UCM::processAppCustomerOverride(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app cust override received: " << (int)message->opCode2;
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "AppCustOverride", "App Customer Override Received, elapsed: " + std::to_string(timer_->getElapsedMS())));
}

//======================================================================================

void EPRI_UCM::processIncompleteMessage(const unsigned char *buffer, unsigned int numBytes)
{
	LOG(WARNING) << "incomplete message received: " << numBytes;
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DER", "DCM", "CTA2045_Message", "IncompleteMsg", "Incomplete Msg Received, elapsed: " + std::to_string(timer_->getElapsedMS())));
}

} //namespace dcm
