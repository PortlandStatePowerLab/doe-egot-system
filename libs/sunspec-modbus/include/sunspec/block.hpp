#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "model.hpp"
#include "point.hpp"

namespace sunspec
{
    struct Block
    {
        uint8_t length;
        std::string id;
        std::string name;
        std::string description;
    };
} // namespace sunspec

#endif // __BLOCK_H__