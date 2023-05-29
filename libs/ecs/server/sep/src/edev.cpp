#include <ecs/server/sep/edev.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

using namespace gsp::edev;

void generateEndDevice(const std::string &lfdi) {
  sep::EndDevice edev;
  edev.subscribable = sep::SubscribableType::kNone;
  edev.href = "/edev/" + lfdi;
  edev.configuration_link.href = "/cfg";
  edev.der_list_link.all = 0;
  edev.der_list_link.href = "/der";
  edev.device_category = sep::DeviceCategoryType::kSmartAppliance;
  edev.device_information_link.href = "/di";
  edev.device_status_link.href = "/ds";
  edev.file_status_link.href = "/fs";
  edev.ip_interface_list_link.all = 0;
  edev.ip_interface_list_link.href = "/ns";
  edev.lfdi = xml::util::Dehexify<sep::HexBinary160>(lfdi);
  edev.load_shed_availability_list_link.all = 0;
  edev.load_shed_availability_list_link.href = "/lsl";
  edev.log_event_list_link.all = 0;
  edev.log_event_list_link.href = "/lel";
  edev.power_status_link.href = "/ps";
  edev.sfdi = xml::util::getSFDI(lfdi);
  edev.changed_time = psu::utilities::getTime();
  edev.enabled = true;
  edev.flow_reservation_request_list_link.all = 0;
  edev.flow_reservation_request_list_link.href = "/frq";
  edev.flow_reservation_response_list_link.all = 0;
  edev.flow_reservation_response_list_link.href = "/frp";
  edev.function_set_assignments_list_link.all = 0;
  edev.function_set_assignments_list_link.href = "/fsa";
  edev.post_rate = 900;
  edev.registration_link.href = "/rg";
  edev.subscription_list_link.all = 0;
  edev.subscription_list_link.href = "/sub";
};

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::EndDevice>();
};