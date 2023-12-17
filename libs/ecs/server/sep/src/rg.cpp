#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <ecs/server/sep/rg.hpp>
#include <fstream>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <sep/models/device_status.hpp>
#include <sep/models/end_device.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

extern std::string g_program_path;
using Sep = boost::char_separator<char>;
using Tokenizer = boost::tokenizer<Sep>;
namespace ecs {
namespace server {
namespace rg {
void Module::generateRegistration(flecs::world &world) {
  boost::filesystem::path path = g_program_path + "/root-ca/registration.csv";
  if (boost::filesystem::exists(path)) {
    std::ifstream file(path.c_str());
    std::string line;
    while (getline(file, line)) {
      Sep sep{","};
      Tokenizer tok(line, sep);
      size_t col = 0;
      std::string lfdi;
      Area area;
      for (const auto &t : tok) {
        switch (col) {
        case 0:
          break;
        case 1:
          lfdi = t;
          break;
        case 2:
          area.id = t;
          break;
        }
        col++;
      }

      sep::Registration rg;
      rg.href = "/rg/" + lfdi;
      rg.poll_rate = 300;
      rg.date_time_registered = psu::utilities::getTime();
      rg.pin = xml::util::generatePIN(lfdi);
      world.entity(rg.href.c_str()).set<sep::Registration>(rg);

      sep::EndDevice edev;
      edev.href = "/edev/" + lfdi;
      edev.changed_time = psu::utilities::getTime();
      edev.post_rate = 300;
      edev.enabled = true;
      sep::RegistrationLink rg_link;
      rg_link.href = rg.href;
      edev.registration_link.emplace(rg_link);
      sep::FlowReservationRequestListLink frq;
      frq.href = "/frq";
      frq.all = 0;
      edev.flow_reservation_request_list_link.emplace(frq);
      sep::FlowReservationResponseListLink frp;
      frp.href = "/frp";
      frp.all = 0;
      edev.flow_reservation_response_list_link.emplace(frp);
      sep::DeviceStatusLink ds;
      ds.href = "/ds";
      edev.device_status_link.emplace(ds);
      edev.device_status_link.emplace(ds);
      edev.lfdi.emplace(xml::util::Dehexify<sep::HexBinary160>(lfdi));
      edev.sfdi = xml::util::getSFDI(lfdi);
      world.entity(edev.href.c_str()).set<sep::EndDevice>(edev);
    }
  } else {
    std::cout << path << " does not exist\n";
  }
};

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Registration>();
  Module::generateRegistration(world);
};
} // namespace rg
} // namespace server
} // namespace ecs
