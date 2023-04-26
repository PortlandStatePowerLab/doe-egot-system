#ifndef __TEXT_MESSAGE_H__
#define __TEXT_MESSAGE_H__
#include "simple_types.hpp"
#include "event.hpp"
#include "priority_type.hpp"

namespace sep {
    struct TextMessageListLink : ListLink {};
    struct TextMessageLink : Link {};

    struct ActiveTextMessageListLink : ListLink {};
    struct ActiveTextMessageLink : Link {};
    
    // Text message such as a notification.
    struct TextMessage : Event {
        String20 originator;
        PriorityType priority;
        std::string text_message;
    };
}

#endif // __TEXT_MESSAGE_H__