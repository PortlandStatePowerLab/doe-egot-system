#ifndef __PSU_UTILITIES_H__
#define __PSU_UTILITIES_H__
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

// C++14 helper
template <class T>
using underlying_type_t = typename std::underlying_type<T>::type;

namespace psu {
namespace utilities {
std::string readFile(const std::string &filename);
std::vector<std::vector<std::string>> readCSV(const std::string &filename);
std::string getProgramPath(char **arg);
int64_t getTime();
int64_t parseTime(const std::string &time, const std::string &format,
                  bool overwrite_date = true);

// c++23 helper
template <class Enum> static underlying_type_t<Enum> ToUnderlyingType(Enum e) {
  return static_cast<underlying_type_t<Enum>>(e);
};

} // namespace utilities

} // namespace psu

#endif // __PSU_UTILITIES_H__