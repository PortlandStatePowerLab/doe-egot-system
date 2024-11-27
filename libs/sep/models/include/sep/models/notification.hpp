#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__
#include "simple_types.hpp"
#include "subscription.hpp"
#include <string>
#include <vector>

namespace sep {
struct NotificaitonListLink : ListLink {};
struct NOtificationLink : Link {};

///
/// Holds the information related to a client subscription to receive updates to
/// a resource automatically. The actual resources may be passed in the
/// Notification by specifying a specific xsi:type for the Resource and passing
/// the full representation.
///
struct Notification : SubscriptionBase {
  enum class Status : UInt8 {
    DEFAULT_STATUS,
    CANCELED,
    MOVED,
    CHANGED,
    DELETED
  };

  std::string new_resource_uri;
  Resource resource;
  Status status;
  std::string subscription_uri;
};

struct NotificaitonList : List {
  std::vector<Notification> notifications;
};
} // namespace sep

#endif // __NOTIFICATION_H__
