#ifndef __XML_UTILITIES_H__
#define __XML_UTILITIES_H__
#include <string>
#include <type_traits>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <ieee-2030.5/models.hpp>

// C++14 helper
template< class T >
using underlying_type_t = typename std::underlying_type<T>::type;

namespace xml
{
    namespace util
    {
        static void SetSchema(boost::property_tree::ptree *pt);
        static boost::property_tree::ptree Treeify(const std::string &xml_str);
        static std::string Stringify(boost::property_tree::ptree *pt);
        template <class Enum>
        static underlying_type_t <Enum> ToUnderlyingType (Enum e);
        template <typename T>
        static std::string Hexify (T number);
        template <typename T>
        static T Dehexify (const std::string hexidecimal);
        template <typename T>
        static uint8_t Checksum (T value);
        static bool validateSFDI (const uint64_t sfdi);
        static uint64_t getSFDI (const std::string& lfdi);
        static uint32_t generatePIN (const std::string& lfdi);
    } // namespace util
};

#endif // __XML_UTILITIES_H__