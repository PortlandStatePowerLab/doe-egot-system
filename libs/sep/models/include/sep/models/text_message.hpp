#ifndef __TEXT_MESSAGE_H__
#define __TEXT_MESSAGE_H__
#include "event.hpp"
#include "priority_type.hpp"
#include "simple_types.hpp"

namespace sep {
struct TextMessageListLink : ListLink {};
struct TextMessageLink : Link {};

struct ActiveTextMessageListLink : ListLink {};
struct ActiveTextMessageLink : Link {};

///
/// Text message such as a notification.
///
struct TextMessage : Event {
  String20 originator;
  PriorityType priority;
  std::string text_message;
};
} // namespace sep

#endif // __TEXT_MESSAGE_H__
