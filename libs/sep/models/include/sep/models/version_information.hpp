#ifndef __VERSION_INFORMATION_H__
#define __VERSION_INFORMATION_H__
#include <string>

namespace sep
{
    struct VersionInformation
    {
        std::string default_namespace;
        std::string element_form_default;
        std::string schema_location;
        std::string target_namespace;
        std::string trace_id;
        std::string version;
    };
}; // namespace sep

#endif // __VERSION_INFORMATION_H__