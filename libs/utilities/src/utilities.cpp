#include <boost/filesystem.hpp>
#include <chrono>
#include <fstream>
#include <sstream>
#include <utilities/utilities.hpp>

using namespace boost::filesystem;

namespace psu {
namespace utilities {
std::string readFile(const std::string &filename) {
  std::string content;

  std::ifstream open_file(filename);
  if (!open_file) {
    return "";
  }

  std::ostringstream oss;
  oss << open_file.rdbuf();
  content = oss.str();
  return content;
}

std::string getProgramPath(char **arg) {
  path p = arg[0];
  p = canonical(p);
  return p.parent_path().string();
}

uint64_t getTime() {
  auto time = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::seconds>(
             time.time_since_epoch())
      .count();
}

} // namespace utilities

} // namespace psu