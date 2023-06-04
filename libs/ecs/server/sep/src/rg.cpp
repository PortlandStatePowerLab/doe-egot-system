#include "sep/models/device_status.hpp"
#include <boost/filesystem.hpp>
#include <ecs/server/sep/rg.hpp>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <sep/models/end_device.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

extern std::string g_program_path;

bool isClientCertification(const boost::filesystem::directory_entry &entry) {
  std::string filename = entry.path().filename().string();
  return filename.find("client") != std::string::npos &&
         entry.path().extension() == ".crt";
}

void gsp::rg::generateRegistration(flecs::world &world) {
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

          auto p = world.entity(lfdi.c_str());

          sep::Registration rg;
          rg.href = "/rg/" + lfdi;
          rg.poll_rate = 900;
          rg.date_time_registered = psu::utilities::getTime();
          rg.pin = xml::util::generatePIN(lfdi);
          world.entity(rg.href.c_str()).child_of(p).set<sep::Registration>(rg);

          sep::EndDevice edev;
          edev.href = "/edev/" + lfdi;
          edev.changed_time = psu::utilities::getTime();
          edev.post_rate = 900;
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
          world.entity(edev.href.c_str()).child_of(p).set<sep::EndDevice>(edev);
          std::cout << "Registered: " << lfdi << std::endl;

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

gsp::rg::Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<Fingerprint>();
  world.component<sep::Registration>();
};