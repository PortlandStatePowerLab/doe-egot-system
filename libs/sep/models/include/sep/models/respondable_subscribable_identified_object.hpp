#ifndef __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#define __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__
#include "respondable_resource.hpp"
#include "simple_types.hpp"
#include "subscribable_type.hpp"
#include <boost/optional.hpp>

namespace sep {
// An IdentifiedObject to which a Response can be requested.
struct RespondableSubscribableIdentifiedObject : RespondableResource {
  mRIDType mrid;
  boost::optional<String32> description;
  boost::optional<VersionType> version;
  SubscribableType subscribable;
};
};     // namespace sep
#endif // __RESPONDABLE_SUBSCRIBABLE_IDENTIFIED_OBJECT_H__