#include <https/client/client.hpp>
#include <trust/cta2045/trust_ucm.hpp>
#include <trust/xml/utils.hpp>
#include <utilities/utilities.hpp>

using namespace cea2045;

namespace trust {
cea2045UCM::cea2045UCM(const https::Context &dtm) : dtm_client(dtm) {
  max_payload_ = cea2045::MaxPayloadLengthCode::LENGTH2;
}

cea2045UCM::~cea2045UCM() {
  // do nothing
}

bool cea2045UCM::isMessageTypeSupported(MessageTypeCode type_code) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "isMessageTypeSupported";
  msg.contents["MessageTypeCode"] = std::to_string(psu::utilities::ToUnderlyingType(type_code));
  dtm_client.Post("/na", trust::Stringify(msg));

  if (type_code == MessageTypeCode::NONE) {
    return false;
  }

  return true;
}

MaxPayloadLengthCode cea2045UCM::getMaxPayload() { return max_payload_; }

void cea2045UCM::processMaxPayloadResponse(MaxPayloadLengthCode payload) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processMaxPayloadResponse";
  msg.contents["MaxPayloadLengthCode"] =
      std::to_string(psu::utilities::ToUnderlyingType(max_payload_));
  dtm_client.Post("/na", trust::Stringify(msg));

  max_payload_ = payload;
}

void cea2045UCM::processDeviceInfoResponse(cea2045DeviceInfoResponse *message) {
  device_info_.device_type = message->getDeviceType();
  device_info_.vendor_id = message->getVendorID();

  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processDeviceInfoResponse";
  msg.contents["deviceType"] = std::to_string(device_info_.device_type);
  msg.contents["vendorId"] = std::to_string(device_info_.vendor_id);
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processCommodityResponse(cea2045CommodityResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processCommodityResponse";
  size_t count = message->getCommodityDataCount();
  for (size_t i = 0; i < count; i++) {
    cea2045CommodityData *data = message->getCommodityData(i);
    int code = static_cast<int>(data->commodityCode);
    int64_t inst = data->getInstantaneousRate();
    int64_t cumm = data->getCumulativeAmount();
   
    std::cout << code << ", " << inst << ", " << cumm << std::endl; 

    commodities_[cta2045::Commodity{
        static_cast<cta2045::Commodity>(code)}] = {inst, cumm};

    msg.contents["commodityCode:"+std::to_string(code)] = std::to_string(code);
    msg.contents["instantaneousRate"+std::to_string(code)] = std::to_string(inst);
    msg.contents["cumulativeAmount"+std::to_string(code)] = std::to_string(cumm);
  }

  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processSetEnergyPriceResponse(
    cea2045IntermediateResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processSetEnergyPriceResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processSetTemperatureOffsetResponse(
    cea2045IntermediateResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processSetTemperatureOffsetResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processGetTemperatureOffsetResponse(
    cea2045GetTemperateOffsetResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processGetTemperatureOffsetResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processSetSetpointsResponse(
    cea2045IntermediateResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processSetSetpointsResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processGetSetpointsResponse(
    cea2045GetSetpointsResponse1 *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processGetSetpointsResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processGetSetpointsResponse(
    cea2045GetSetpointsResponse2 *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processGetSetpointsResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processStartCyclingResponse(
    cea2045IntermediateResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processStartCyclingResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processTerminateCyclingResponse(
    cea2045IntermediateResponse *message)

{
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processTerminateCyclingResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processGetPresentTemperatureResponse(
    cea2045GetPresentTemperatureResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processGetPresentTemperatureResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processGetUTCTimeResponse(cea2045GetUTCTimeResponse *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processGetUTCTimeResponse";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processAckReceived(MessageCode code) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processAckReceived";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processNakReceived(LinkLayerNakCode nak, MessageCode code) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processNakReceived";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processAppAckReceived(cea2045Basic *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processAppAckReceived";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processAppNakReceived(cea2045Basic *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processAppNakReceived";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processOperationalStateReceived(cea2045Basic *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processOperationalStateReceived";
  int op1 = (int)message->opCode1;
  int op2 = (int)message->opCode2;
  std::cout << "Op Codes: " << op1 << ", " << op2 << std::endl;
  msg.contents["opCode1"] = std::to_string(op1);
  msg.contents["opCode2"] = std::to_string(op2);
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processAppCustomerOverride(cea2045Basic *message) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processAppCustomerOverride";
  dtm_client.Post("/na", trust::Stringify(msg));
}

void cea2045UCM::processIncompleteMessage(const unsigned char *buffer,
                                          unsigned int byte_count) {
  trust::Message msg;
  msg.to = "DCM";
  msg.from = "DER";
  msg.timestamp = psu::utilities::getTime();
  msg.contents["response"] = "processIncompleteMessage";
  dtm_client.Post("/na", trust::Stringify(msg));
}

} // namespace trust
