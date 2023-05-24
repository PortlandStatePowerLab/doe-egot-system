#ifndef __RESPONSE_SET_H__
#define __RESPONSE_SET_H__
#include "response.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include <boost/optional.hpp>
#include <vector>

namespace sep {
struct ResponseSetListLink : ListLink {};
struct ReponseSetLink : Link {};

// The Response object is the generic response data repository
// which is extended for specific function sets.
struct ResponseSet : IdentifiedObject {
  boost::optional<ResponseListLink> response_list_link;
};

struct ResponseSetList : List {
  std::vector<ResponseSet> response_sets;
  UInt32 poll_rate;
};

} // namespace sep
#endif // __RESPONSE_SET_H__