#ifndef __SUBSCRIPTION_H__
#define __SUBSCRIPTION_H__
#include "simple_types.hpp"

namespace sep {
struct SubscriptionBase : Resource {
  Link subscribed_resource;
};

///
/// Indicates a condition that must be satisfied for the Notification to be
/// triggered.
///
struct Condition {
  UInt8 attribute_identifier;
  Int48 lower_threshold;
  Int48 upper_threshold;
};

struct SubscriptionListLink : ListLink {};
struct SubscriptionLink : Link {};

///
/// Holds the information related to a client subscription to receive updates to
/// a resource automatically.
///
struct Subscription : SubscriptionBase {
  enum class Encoding : UInt8 { APPLICATION_SEP_XML, APPLICATION_SEP_EXI };

  Condition condition;
  Encoding encoding;
  String16 level;
  UInt32 limit;
  Link notification_uri;
};
} // namespace sep

#endif // __SUBSCRIPTION_H__
