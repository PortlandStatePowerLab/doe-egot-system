#ifndef __DER_H__
#define __DER_H__
#include "der_availability.hpp"
#include "der_capability.hpp"
#include "der_program.hpp"
#include "der_settings.hpp"
#include "der_status.hpp"
#include "subscribable_resource.hpp"
#include "usage_point_base.hpp"
#include <boost/optional.hpp>
#include <vector>

namespace sep {
///
/// Contains links to DER resources.
///
struct DER : SubscribableResource {
  boost::optional<AssociatedDERProgramListLink>
      associated_der_program_list_link;
  boost::optional<AssociatedUsagePointLink> associated_usage_program_link;
  boost::optional<CurrentDERProgramLink> current_der_program_link;
  boost::optional<DERAvailabilityLink> der_availability_link;
  boost::optional<DERCapabilityLink> der_capability_link;
  boost::optional<DERSettingsLink> der_settings_link;
  boost::optional<DERStatusLink> der_status_link;
};

struct DERListLink : ListLink {};

struct DERList : List {
  std::vector<DER> ders;
  sep::UInt32 poll_rate = 900;
};

} // namespace sep

#endif // __DER_H__
