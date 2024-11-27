#include "sep/models/der_availability.hpp"
#include "sep/models/der_status.hpp"
#include <ecs/client/sep/der.hpp>
#include <iostream>
#include <sep/xml/der_availability_adapter.hpp>
#include <sep/xml/der_capability_adapter.hpp>
#include <sep/xml/der_settings_adapter.hpp>
#include <sep/xml/der_status_adapter.hpp>
#include <trust/https/client.hpp>

using namespace ecs::client::der;

void Module::getDERCapabilities(flecs::entity e, sep::DERCapabilityLink &link) {
  auto resp = trust::HttpsClient::getInstance().Get(link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::DERCapability dercap;
    xml::Parse(msg, &dercap);
    e.set<sep::DERCapability>(dercap);
  }
};
void Module::getDERSettings(flecs::entity e, sep::DERSettingsLink &link) {
  auto resp = trust::HttpsClient::getInstance().Get(link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::DERSettings derg;
    xml::Parse(msg, &derg);
    e.set<sep::DERSettings>(derg);
  }
};
void Module::getDERStatus(flecs::entity e, sep::DERStatusLink &link) {
  auto resp = trust::HttpsClient::getInstance().Get(link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::DERStatus ders;
    xml::Parse(msg, &ders);
    e.set<sep::DERStatus>(ders);
  }
};
void Module::getDERAvailablity(flecs::entity e,
                               sep::DERAvailabilityLink &link) {
  auto resp = trust::HttpsClient::getInstance().Get(link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::DERAvailability dera;
    xml::Parse(msg, &dera);
    e.set<sep::DERAvailability>(dera);
  }
};

void Module::updateDER(flecs::entity e, sep::DERList &list) {
  auto der = list.ders[0]; // should never be more than one der in list
  if (der.der_capability_link.is_initialized()) {
    e.set<sep::DERCapabilityLink>(der.der_capability_link.value());
  }
  if (der.der_settings_link.is_initialized()) {
    e.set<sep::DERSettingsLink>(der.der_settings_link.value());
  }
  if (der.der_status_link.is_initialized()) {
    e.set<sep::DERStatusLink>(der.der_status_link.value());
  }
  if (der.der_availability_link.is_initialized()) {
    e.set<sep::DERAvailabilityLink>(der.der_availability_link.value());
  }
};

Module::Module(flecs::world &world) {
  world.component<sep::DER>();
  world.component<sep::DERCapability>();
  world.component<sep::DERCapabilityLink>();
  world.component<sep::DERSettings>();
  world.component<sep::DERSettingsLink>();
  world.component<sep::DERStatus>();
  world.component<sep::DERStatusLink>();
  world.component<sep::DERAvailability>();
  world.component<sep::DERAvailabilityLink>();

  world.observer<sep::DERList>("updateder")
      .event(flecs::OnSet)
      .each(Module::updateDER);

  world.observer<sep::DERCapabilityLink>("dercaplink")
      .event(flecs::OnSet)
      .each(Module::getDERCapabilities);

  world.observer<sep::DERSettingsLink>("derglink")
      .event(flecs::OnSet)
      .each(Module::getDERSettings);

  world.observer<sep::DERStatusLink>("derslink")
      .event(flecs::OnSet)
      .each(Module::getDERStatus);

  world.observer<sep::DERAvailabilityLink>("deralink")
      .event(flecs::OnSet)
      .each(Module::getDERAvailablity);
};
