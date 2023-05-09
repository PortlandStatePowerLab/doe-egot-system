#ifndef __MESSAGING_PROGRAM_H__
#define __MESSAGING_PROGRAM_H__
#include "simple_types.hpp"
#include "subscribable_identified_object.hpp"
#include "text_message.hpp"
#include "locale_type.hpp"
#include "primacy_type.hpp"

namespace sep{
    struct MessagingProgramListLink : ListLink {};
    struct MessagingProgramLink : Link {};
    
    // Provides a container for collections of text messages.
    struct MessagingProgram : SubscribableIdentifiedObject {
        ActiveTextMessageListLink active_text_message_list_link;
        LocaleType locale;
        PrimacyType primacy;
        TextMessageListLink text_message_list_link;
    };
}

#endif // __MESSAGING_PROGRAM_H__