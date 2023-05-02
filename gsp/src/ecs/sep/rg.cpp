#include "include/sep/rg.hpp"
#include "include/sep/access.hpp"
#include <boost/filesystem.hpp>

bool isClientCertification(const boost::filesystem::directory_entry &entry) {
  std::string filename = entry.path().filename().string();
  return filename.find("client") != std::string::npos &&
         entry.path().extension() == ".crt";
}

void generateRegistration(const std::string &lfdi) {
  sep::Registration rg;
  rg.href = "/rg/" + lfdi;
  rg.poll_rate = 900;
  rg.date_time_registered = psu::utilities::getTime();
  rg.pin = xml::util::generatePIN(lfdi);

  access::Fingerprint fingerprint;
  fingerprint.value = lfdi;

  World::getInstance()
      .world.entity()
      .set<sep::Registration>(rg)
      .set<access::Fingerprint>(fingerprint)
      .set<access::Subject>(subject);
};

void Initialize(const std::string &doc_root) {
  generateDeviceCapabilities();
  generateTime();

  boost::filesystem::path p = doc_root + "/root-ca";
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
            oss << std::hex << (int)md[i];
          };
          std::string lfdi = oss.str().substr(0, 40);

          generateEndDevice(lfdi);
          generateRegistration(lfdi);

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

namespace rg {
Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<access::Fingerprint>();
};
} // namespace rg