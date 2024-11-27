#include "sep/models/der.hpp"
#include "sep/models/flow_reservation_request.hpp"
#include "sep/models/flow_reservation_response.hpp"
#include "sep/models/registration.hpp"
#include <ecs/client/sep/edev.hpp>
#include <ecs/client/sep/rg.hpp>
#include <sep/models/end_device.hpp>
#include <sep/xml/der_adapter.hpp>
#include <sep/xml/flow_reservation_response_adapter.hpp>
#include <sep/xml/registration_adapter.hpp>
#include <trust/https/client.hpp>

using namespace ecs::client::edev;

void Module::getRegistration(flecs::entity e, sep::RegistrationLink &link) {
  auto resp = trust::HttpsClient::getInstance().Get(link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::Registration rg;
    xml::Parse(msg, &rg);
    e.set<sep::Registration>(rg);
  }
};

void Module::getDERListLink(flecs::entity e, sep::DERListLink &list_link) {
  auto resp = trust::HttpsClient::getInstance().Get(list_link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::DERList ders;
    xml::Parse(msg, &ders);
    e.set<sep::DERList>(ders);
  }
};

void Module::getFRPListLink(flecs::entity e,
                            sep::FlowReservationResponseListLink &list_link) {
  auto resp = trust::HttpsClient::getInstance().Get(list_link.href);
  if (resp.result_int() == 200) {
    std::string msg = boost::beast::buffers_to_string(resp.body().data());
    std::cout << msg << std::endl;
    sep::FlowReservationResponseList frp;
    xml::Parse(msg, &frp);
    e.set<sep::FlowReservationResponseList>(frp);
  }
};

Module::Module(flecs::world &world) {
  world.module<Module>();

  world.component<sep::EndDevice>();
  world.component<sep::DERListLink>();
  world.component<sep::RegistrationLink>();
  world.component<sep::FlowReservationRequestList>();
  world.component<sep::FlowReservationRequestListLink>();
  world.component<sep::FlowReservationResponseListLink>();

  world.observer<sep::EndDevice>("enddevice")
      .event(flecs::OnSet)
      .each([](flecs::entity e, sep::EndDevice &edev) {
        if (edev.registration_link.has_value()) {
          e.set<sep::RegistrationLink>(edev.registration_link.value());
        }
        if (edev.der_list_link.has_value()) {
          e.set<sep::DERListLink>(edev.der_list_link.value());
        }
        if (edev.flow_reservation_request_list_link.has_value()) {
          e.set<sep::FlowReservationRequestListLink>(
              edev.flow_reservation_request_list_link.value());
        }
        if (edev.flow_reservation_response_list_link.has_value()) {
          e.set<sep::FlowReservationResponseListLink>(
              edev.flow_reservation_response_list_link.value());
        }
      });

  world.observer<sep::RegistrationLink>("rglink")
      .event(flecs::OnSet)
      .each(Module::getRegistration);

  world.observer<sep::DERListLink>("derlistlink")
      .event(flecs::OnSet)
      .each(Module::getDERListLink);

  world.observer<sep::FlowReservationResponseListLink>("frplistlink")
      .event(flecs::OnSet)
      .each(Module::getFRPListLink);
};
