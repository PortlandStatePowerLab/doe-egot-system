#ifndef __ABSTRACT_DEVICE_H__
#define __ABSTRACT_DEVICE_H__
#include "configuration.hpp"
#include "der.hpp"
#include "device_category_type.hpp"
#include "device_information.hpp"
#include "device_status.hpp"
#include "file_status.hpp"
#include "ip_interface.hpp"
#include "load_shed_availability.hpp"
#include "log_event.hpp"
#include "power_status.hpp"
#include "simple_types.hpp"
#include "subscribable_resource.hpp"
#include <boost/optional.hpp>

namespace sep {
///
/// The EndDevice providing the resources available within the
/// DeviceCapabilities.
///
struct AbstractDevice : SubscribableResource {
  SFDIType sfdi;
  boost::optional<ConfigurationLink> configuration_link;
  boost::optional<DERListLink> der_list_link;
  boost::optional<DeviceCategoryType> device_category;
  boost::optional<DeviceInformationLink> device_information_link;
  boost::optional<DeviceStatusLink> device_status_link;
  boost::optional<FileStatusLink> file_status_link;
  boost::optional<IPInterfaceListLink> ip_interface_list_link;
  boost::optional<HexBinary160> lfdi;
  boost::optional<LoadShedAvailabilityListLink>
      load_shed_availability_list_link;
  boost::optional<LogEventListLink> log_event_list_link;
  boost::optional<PowerStatusLink> power_status_link;
};

} // namespace sep

#endif // __ABSTRACT_DEVICE_H__
