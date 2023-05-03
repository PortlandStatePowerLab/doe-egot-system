#include "include/sep/rg.hpp"
#include <boost/filesystem.hpp>
#include <utilities/utilities.hpp>
#include <xml/utilities.hpp>

using namespace gsp::rg;
extern std::string g_program_path;

bool isClientCertification(const boost::filesystem::directory_entry &entry) {
  std::string filename = entry.path().filename().string();
  return filename.find("client") != std::string::npos &&
         entry.path().extension() == ".crt";
}

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
            oss << std::hex << (int)md[i];
          };
          std::string lfdi = oss.str().substr(0, 40);

          Fingerprint fingerprint;
          fingerprint.lfdi = lfdi;

          auto p = world.entity(lfdi).set<gsp::rg::Fingerprint>({fingerprint});

          sep::Registration rg;
          rg.href = "/rg/" + lfdi;
          rg.poll_rate = 900;
          rg.date_time_registered = psu::utilities::getTime();
          rg.pin = xml::util::generatePIN(lfdi);

          world.entity().child_of(p).set<sep::Registration>({rg});

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
  world.component<Fingerprint>();
  world.component<sep::Registration>();
  generateRegistration(world);
};