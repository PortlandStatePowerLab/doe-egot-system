#ifndef __HREF_H__
#define __HREF_H__

#include "query.hpp"
#include "uri.hpp"
#include <boost/multiprecision/cpp_int.hpp>

struct Href
{
    boost::multiprecision::uint256_t lfdi;
    Uri uri;
    Query query;
};

#endif // __HREF_H__