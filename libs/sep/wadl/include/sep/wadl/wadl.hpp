#ifndef __WADL_H__
#define __WADL_H__
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace sep {
///
/// container for specified uri properties such as access control and response
/// code
///
struct WADLResource {
  struct Properties {
    bool allow;
    std::vector<std::string> content_type;
    std::vector<unsigned int> status;
    std::vector<std::string> params;
  };

  uint16_t methods_bit_mask;
  std::unordered_map<std::string, Properties> properties;
};

///
/// The WADL class is a convience class to map server uri access and response
/// status codes. A server can get all properties mapped to a specified uri and
/// verify the current request to ensure alignment.
///
class WADL {
public:
  // rule of 5
  WADL(WADL &other) = delete;            // clonable
  void operator=(const WADL &) = delete; // assignable
  static WADL *getInstance(const std::string &wadl_path);
  WADLResource getResource(const std::string &uri);

protected:
  WADL(const std::string &wadl_path);
  ~WADL() noexcept;

private:
  std::unordered_map<std::string, WADLResource> wadl_;

private:
  // thread-safe singleton instance
  static WADL *instance_;
  static std::mutex mutex_;
};
} // namespace sep

#endif // __WADL_H__
