#ifndef __QUERY_H__
#define __QUERY_H__

#include <cstdint>

struct Query
{
    uint16_t start;
    uint16_t after;
    uint16_t length;
};

#endif // __QUERY_H__