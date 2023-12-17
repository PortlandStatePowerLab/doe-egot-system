#ifndef __HREF_H__
#define __HREF_H__

#include <cstdint>
#include <string>

namespace ecs {
namespace server {

///
/// Utility structure to handle query string parameters
///
/// \param start is the index value of the list requested to start from
/// \param after can be used instead of start to point to where the index should
/// begin
/// \param limit ensures the list remains under the specified size
///
struct Query {
  uint16_t start;
  uint64_t after;
  uint16_t limit;
};

///
/// Utility structure to capture parameters from client requests
///
/// \param lfdi is the fingerprint of the client making the request
/// \param uri is the path to the resource requested
/// \param subject is the base path of the uri and typically used for lists of
/// resources that don't have a single URI
/// \param Query referenced above
///
struct Href {
  std::string lfdi;
  std::string uri;
  std::string subject;
  Query query;
};

} // namespace server
} // namespace ecs
#endif // __HREF_H__
