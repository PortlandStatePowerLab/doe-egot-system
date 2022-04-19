#ifndef __PSU_UTILITIES_H__
#define __PSU_UTILITIES_H__
#include <string>
#include <cstdint>

namespace psu
{
    namespace utilities
    {
        std::string readFile(const std::string& filename);
        std::string getProgramPath(char** arg);
        uint64_t getTime(); 
    } // namespace utilities

} // namespace psu

#endif // __PSU_UTILITIES_H__