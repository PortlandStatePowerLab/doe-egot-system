#include <boost/filesystem.hpp>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
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

std::vector<std::vector<std::string>> readCSV(const std::string &filename) {
  std::vector<std::vector<std::string>> content = {};

  std::ifstream open_file(filename);
  if (!open_file) {
    return content;
  }

  std::stringstream file;
  file << open_file.rdbuf();

  char delim = ',';
  std::string line;
  std::string value;
  while (std::getline(file, line)) {
    std::vector<std::string> values;
    std::stringstream ssr;
    ssr << line;
    while (std::getline(ssr, value, delim)) {
      values.push_back(value);
    }
    content.push_back(values);
  }
  return content;
}

std::string getProgramPath(char **arg) {
  path p = arg[0];
  p = canonical(p);
  return p.parent_path().string();
}

int64_t getTime() {
  auto time = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::seconds>(
             time.time_since_epoch())
      .count();
}

int64_t parseTime(const std::string &time, const std::string &format,
                  bool overwrite_date) {
  std::stringstream ss(time);
  std::tm t = {};
  ss >> std::get_time(&t, format.c_str());
  if (overwrite_date) {
    int64_t now = getTime();
    std::tm now_tp = *std::localtime(&now);
    t.tm_mday = now_tp.tm_mday;
    t.tm_mon = now_tp.tm_mon;
    t.tm_year = now_tp.tm_year;
    t.tm_wday = now_tp.tm_wday;
    t.tm_yday = now_tp.tm_yday;
    t.tm_isdst = now_tp.tm_isdst;
  }
  std::cout << asctime(&t) << std::endl;
  return mktime(&t);
}
} // namespace utilities

} // namespace psu