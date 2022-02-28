#ifndef __HREF_H__
#define __HREF_H__

#include <cstdint>
#include <string>

struct Query
{
    uint16_t start;
    uint16_t after;
    uint16_t length;
};

struct Href
{
    std::string lfdi;
    std::string uri;
    Query query;
};

#endif // __HREF_H__