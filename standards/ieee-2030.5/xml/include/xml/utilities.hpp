#ifndef __XML_UTILITIES_H__
#define __XML_UTILITIES_H__
#include <string>
#include <type_traits>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/multiprecision/cpp_int.hpp>

// C++14 helper
template< class T >
using underlying_type_t = typename std::underlying_type<T>::type;

namespace xml
{
    namespace util
    {
        static void SetSchema(boost::property_tree::ptree *pt)
        {
            // this part overwrite schema info for validation or fills in the attrs that are needed
            // TODO: it would be nice to figure out how to validate without overwriting the xsi stuff
            // TODO: This function doesn't work currently
            std::string root = pt->begin()->first;
            pt->put(root + ".<xmlattr>.xmlns", "urn:ieee:std:2030.5:ns");
            pt->put(root + ".<xmlattr>.xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
            pt->put(root + ".<xmlattr>.xsi:schemaLocation", "urn:ieee:std:2030.5:ns sep.xsd");
        };

        static boost::property_tree::ptree Treeify(const std::string &xml_str)
        {
            // utility function to help translate strings to/from objects
            std::stringstream ss (xml_str);
            boost::property_tree::ptree pt;
            boost::property_tree::xml_parser::read_xml(ss, pt);
            return pt;
        };

        static std::string Stringify(boost::property_tree::ptree* pt)
        {
            // utility function to help translate strings to/from objects
            SetSchema(pt);
            std::stringstream ss;
            boost::property_tree::xml_parser::write_xml(ss, *pt);
            return ss.str();
        };

        // c++23 helper
        template <class Enum>
        static underlying_type_t<Enum> ToUnderlyingType(Enum e)
        {
            return static_cast<underlying_type_t<Enum>>(e);
        };

        template <typename T>
        static std::string Hexify(T number)
        {
            std::string hex_str;
            bool type_is_number = std::is_integral<T>::value || boost::multiprecision::is_number<T>::value;
            if (!type_is_number)
            {
                return "";
                
            }

            std::stringstream ss;
            ss << std::hex << number;
            hex_str = ss.str();

            bool needs_padding = hex_str.length() % 2 > 0;
            if (needs_padding) 
            {
                hex_str.insert(0,"0");
            }

            return hex_str;
        };

        template <typename T>
        static T Dehexify(const std::string hexidecimal)
        {
            T number;
            std::stringstream ss;
            ss << std::hex << hexidecimal;
            ss >> number;
            return number;
        };

        template <typename T>
        static uint8_t Checksum(T value)
        {
            T remainder, total;
            for (total = 0; value > 0; value = value / 10)
            {
                remainder = value % 10;
                total += remainder;
            }

            uint8_t checksum = total % 10;
            return (checksum == 0)
                ? checksum
                : 10 - (total % 10);
        };

        static bool validateSFDI(const uint64_t sfdi)
        {
            return Checksum(sfdi) == 0;
        };

        static uint64_t getSFDI(const std::string &lfdi)
        {
            uint64_t sfdi = Dehexify<uint64_t>(lfdi.substr(0, 9));
            uint8_t checksum = Checksum(sfdi);
            return (sfdi * 10) + checksum;
        };

        static uint32_t generatePIN(const std::string &lfdi)
        {
            uint64_t sfdi = Dehexify<uint64_t>(lfdi.substr(0, 9));
            std::string pin = std::to_string(sfdi);
            sfdi = std::stol(pin.substr(0, 5));
            uint8_t checksum = Checksum(sfdi);
            return (sfdi * 10) + checksum;
        };

    }; // namespace util
}; // namespace sep

#endif // __XML_UTILITIES_H__