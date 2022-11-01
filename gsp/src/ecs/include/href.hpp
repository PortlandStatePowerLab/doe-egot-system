#ifndef __HREF_H__
#define __HREF_H__

#include <cstdint>
#include <string>

struct Query
{
    uint16_t start;
    uint64_t after;
    uint16_t limit;
};

struct Href
{
    std::string lfdi;
    std::string uri;
    std::string subject;
    Query query;
};

#endif // __HREF_H__