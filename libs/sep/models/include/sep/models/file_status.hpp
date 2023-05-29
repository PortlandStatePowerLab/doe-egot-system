#ifndef __FILE_STATUS_H__
#define __FILE_STATUS_H__
#include "simple_types.hpp"

namespace sep {
    struct FileStatusListLink : ListLink {};
    struct FileStatusLink : Link {};

    // This object provides status of device file load and activation operations.
    struct FileStatus : Resource {
        // TODO
    };
}

#endif // __FILE_STATUS_H__