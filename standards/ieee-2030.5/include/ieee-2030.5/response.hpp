#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include <boost/multiprecision/cpp_int.hpp>
#include "resource.hpp"
#include "time_type.hpp"
#include "mrid_type.hpp"

namespace sep
{
    // The Response object is the generic response data repository 
    // which is extended for specific function sets.
    struct Response : Resource
    {
        TimeType create_date_time;
        boost::multiprecision::uint256_t lfdi;
        uint8_t status;
        MRIDType subject;
    };
    
} // namespace sep

#endif // __RESPONSE_H__