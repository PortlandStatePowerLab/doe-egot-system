#ifndef __PSU_UTILITIES_H__
#define __PSU_UTILITIES_H__
#include <string>
#include <cstdint>
#include <type_traits>

// C++14 helper
template< class T >
using underlying_type_t = typename std::underlying_type<T>::type;

namespace psu
{
    namespace utilities
    {
        std::string readFile(const std::string& filename);
        std::string getProgramPath(char** arg);
        uint64_t getTime(); 
        
        // c++23 helper
        template <class Enum>
        static underlying_type_t<Enum> ToUnderlyingType(Enum e)
        {
            return static_cast<underlying_type_t<Enum>>(e);
        };

    } // namespace utilities

} // namespace psu

#endif // __PSU_UTILITIES_H__