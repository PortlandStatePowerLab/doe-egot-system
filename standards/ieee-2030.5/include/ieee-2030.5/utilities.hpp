#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include <type_traits>
 
namespace util
{
    template<typename E>
    static constexpr auto enum_value(E e) -> typename std::underlying_type<E>::type 
    {
    return static_cast<typename std::underlying_type<E>::type>(e);
    }
} // namespace util



#endif // __UTILITIES_H__