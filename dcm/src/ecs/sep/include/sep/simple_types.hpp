#ifndef __SIMPLE_TYPES_H__
#define __SIMPLE_TYPES_H__
#include <cstdint>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

namespace sep {
    
using HexBinary8 = uint8_t;
using HexBinary16 = uint16_t;
using HexBinary32 = uint32_t;
using HexBinary48 = uint64_t;
using HexBinary64 = uint64_t;
using HexBinary128 = boost::multiprecision::uint128_t;
using HexBinary160 = boost::multiprecision::uint256_t;
using String6 = std::string;
using String16 = std::string;
using String20 = std::string;
using String32 = std::string;
using String42 = std::string;
using String192 = std::string;
using UInt8 = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt40 = uint64_t;
using UInt48 = uint64_t;
using UInt64 = uint64_t;
using Int8 = int8_t;
using Int16 = int16_t;
using Int32 = int32_t;
using Int48 = int64_t;
using Int64 = int64_t;
using VersionType = UInt16;
using TimeType = Int64;
using mRIDType = HexBinary128;

struct Resource {
    std::string href;
};

struct Link {
    std::string href;
};

struct List : Resource {
    UInt32 all;
};

struct ListLink : Link {
    UInt32 all;
};

struct IdentifiedObject : Resource {
    mRIDType mrid;
    String32 description;
    VersionType version;
};

}
#endif // __SIMPLE_TYPES_H__