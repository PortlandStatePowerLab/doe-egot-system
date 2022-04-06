#ifndef __ADAPTER_H__
#define __ADAPTER_H__
#include <string>
#include <sstream>
#include <type_traits>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <ieee-2030.5/models.hpp>

// C++14 helper
template< class T >
using underlying_type_t = typename std::underlying_type<T>::type;

namespace xml
{
    namespace util
    {
        void SetSchema(boost::property_tree::ptree *pt);
        boost::property_tree::ptree Treeify(const std::string &xml_str);
        std::string Stringify(boost::property_tree::ptree pt);
        template <class Enum>
        underlying_type_t <Enum> ToUnderlyingType (Enum e);
        template <typename T>
        std::string Hexify (T number);
        template <typename T>
        T Dehexify (const std::string hexidecimal);
        template <typename T>
        uint8_t Checksum (T value);
        bool validateSFDI (const uint64_t sfdi);
        uint64_t getSFDI (const std::string& lfdi);
        uint32_t generatePIN (const std::string& lfdi);
    } // namespace util

    // Active Power
    std::string Serialize(const sep::ActivePower &active_power);
    void Parse (const std::string &xml_str, sep::ActivePower *active_power);

    // Abstract Device
    std::string Serialize(const sep::AbstractDevice &abstract_device);
    void Parse (const std::string &xml_str, sep::AbstractDevice *abstract_device);

    // Flow Reservation Request
    std::string Serialize(const sep::FlowReservationRequest &fr_request);
    void Parse(const std::string &xml_str, sep::FlowReservationRequest *fr_request);

    // Flow Reservation Response
    std::string Serialize(const sep::FlowReservationResponse &fr_response);
    void Parse(const std::string &xml_str, sep::FlowReservationResponse *fr_response);

    // Device Capability
    std::string Serialize(const sep::DeviceCapability &dcap);
    void Parse(const std::string &xml_str, sep::DeviceCapability *dcap);

    // End Device
    std::string Serialize(const sep::EndDevice &edev);
    void Parse(const std::string &xml_str, sep::EndDevice *edev);

    // Self Device
    std::string Serialize(const sep::SelfDevice &sdev);
    void Parse(const std::string &xml_str, sep::SelfDevice *sdev);

    // Registration
    std::string Serialize(const sep::Registration &rg);
    void Parse (const std::string &xml_str, sep::Registration* rg);

    // Time
    std::string Serialize(const sep::Time &time);
    void Parse(const std::string &xml_str, sep::Time *time);
} // namespace xml

#endif // __ADAPTER_H__