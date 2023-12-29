#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <ecs/server/sep/rg.hpp>
#include <iostream>
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

bool isClientCertification(const boost::filesystem::directory_entry &entry) {
  std::string filename = entry.path().filename().string();
  return filename.find("client") != std::string::npos &&
         entry.path().extension() == ".crt";
};

namespace ecs {
namespace server {
namespace rg {
void generateRegistration(flecs::world &world) {
  boost::filesystem::path p = g_program_path + "/root-ca";
  if (boost::filesystem::exists(p)) // does path p actually exist?
  {
    if (boost::filesystem::is_directory(p)) // is path p a directory?
    {
      for (auto &entry : boost::make_iterator_range(
               boost::filesystem::directory_iterator(p), {})) {
        if (isClientCertification(entry)) {
          FILE *fp = fopen(entry.path().c_str(), "r");
          X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);

          // fingerprint
          unsigned char md[EVP_MAX_MD_SIZE];
          unsigned int n;
          X509_digest(cert, EVP_sha256(), md, &n);

          // 40 hex character length for fingerprint
          std::ostringstream oss;
          for (size_t i = 0; i < n; i++) {
            oss << std::uppercase << std::hex << (int)md[i];
          };
          std::string lfdi = oss.str().substr(0, 40);
          std::cout << "registered : " << lfdi << std::endl;
          auto p = world.entity(lfdi.c_str());

          sep::Registration rg;
          rg.href = "/rg/" + lfdi;
          rg.poll_rate = 300;
          rg.date_time_registered = psu::utilities::getTime();
          rg.pin = xml::util::generatePIN(lfdi);
          world.entity(rg.href.c_str()).child_of(p).set<sep::Registration>(rg);

          sep::EndDevice edev;
          edev.href = "/edev/" + lfdi;
          edev.changed_time = psu::utilities::getTime();
          edev.post_rate = 300;
          edev.enabled = true;
          sep::RegistrationLink rg_link;
          rg_link.href = rg.href;
          edev.registration_link.emplace(rg_link);
          sep::DERListLink der_ll;
          der_ll.href = "/der";
          der_ll.all = 0;

          edev.der_list_link.emplace(der_ll);
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
          world.entity(edev.href.c_str()).child_of(p).set<sep::EndDevice>(edev);

          sep::DER der;
          der.href = "/der/" + lfdi;
          sep::DERCapabilityLink derc;
          derc.href = "/dercap";
          der.der_capability_link.emplace(derc);
          sep::DERSettingsLink derg;
          derg.href = "/derg";
          der.der_settings_link.emplace(derg);
          sep::DERStatusLink ders;
          ders.href = "/ders";
          der.der_status_link.emplace(ders);
          sep::DERAvailabilityLink dera;
          dera.href = "/dera";
          der.der_availability_link.emplace(dera);
          world.entity(der.href.c_str()).child_of(p).set<sep::DER>(der);
          X509_free(cert);
          fclose(fp);
        }
      }
    } else {
      std::cout << p << " exists, but is not a regular file or directory\n";
    }
  } else {
    std::cout << p << " does not exist\n";
  }
};

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Registration>();
};
} // namespace rg
} // namespace server
} // namespace ecs
