#include "include/xml/adapter.hpp"
#include <iostream>

namespace xml
{
    namespace util
    {
        void SetSchema(boost::property_tree::ptree *pt)
        {
            // this part overwrite schema info for validation or fills in the attrs that are needed
            // TODO: it would be nice to figure out how to validate without overwriting the xsi stuff
            // TODO: This function doesn't work currently
            std::string root = pt->begin()->first;
            pt->put(root + ".<xmlattr>.xmlns", "urn:ieee:std:2030.5:ns");
            pt->put(root + ".<xmlattr>.xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
            pt->put(root + ".<xmlattr>.xsi:schemaLocation", "urn:ieee:std:2030.5:ns sep.xsd");
        };

        boost::property_tree::ptree Treeify(const std::string &xml_str)
        {
            // utility function to help translate strings to/from objects
            std::stringstream ss;
            ss << xml_str;
            boost::property_tree::ptree pt;
            boost::property_tree::xml_parser::read_xml(ss, pt);
            return pt;
        };

        std::string Stringify(boost::property_tree::ptree pt)
        {
            // utility function to help translate strings to/from objects
            SetSchema(&pt);
            std::stringstream ss;
            boost::property_tree::xml_parser::write_xml(ss, pt);
            return ss.str();
        };

        // c++23 helper
        template <class Enum>
        underlying_type_t <Enum> ToUnderlyingType (Enum e)
        {
            return static_cast<underlying_type_t<Enum>>(e);
        };

        template<typename T>
        std::string Hexify(T number) 
        {
            std::string hex_str;
            if (std::is_integral<T>::value)
            {
                std::stringstream ss;
                ss << std::uppercase << std::hex << number;
                hex_str = ss.str();
                if (hex_str.length() % 2 > 0)
                {
                    hex_str.append("0");
                    return hex_str;
                }
            }
            return hex_str;
        }
        
        template<typename T>
        T Dehexify(const std::string hexidecimal) 
        {
            T number;
            std::stringstream ss;
            ss << std::hex << hexidecimal;
            ss >> number;
            return number;
        };
                
        }; // namespace util

    // Abstract Device
    std::string Serialize(const sep::AbstractDevice &abstract_device)
    {
        boost::property_tree::ptree pt;
        pt.put("AbstractDevice.<xmlattr>.subscribable", xml::util::ToUnderlyingType(abstract_device.subscribable));
        pt.put("AbstractDevice.<xmlattr>.href", abstract_device.href);
        pt.put("AbstractDevice.ConfigurationLink.<xmlattr>.href", abstract_device.configuration_link.href);
        pt.put("AbstractDevice.DERListLink", abstract_device.der_list_link.all);
        pt.put("AbstractDevice.DERListLink", abstract_device.der_list_link.href);
        pt.put("AbstractDevice.deviceCategory", xml::util::ToUnderlyingType(abstract_device.device_category));
        pt.put("AbstractDevice.DeviceInformationLink.<xmlattr>.href", abstract_device.device_information_link.href);
        pt.put("AbstractDevice.DeviceStatusLink.<xmlattr>.href",abstract_device.device_status_link.href);
        pt.put("AbstractDevice.FileStatusLink.<xmlattr>.href",abstract_device.file_status_link.href);
        pt.put("AbstractDevice.IPInterfaceListLink.<xmlattr>.all",abstract_device.ip_interface_list_link.all);
        pt.put("AbstractDevice.IPInterfaceListLink.<xmlattr>.href",abstract_device.ip_interface_list_link.href);
        pt.put("AbstractDevice.lFDI",xml::util::Hexify(abstract_device.lfdi));
        pt.put("AbstractDevice.LoadShedAvailabilityListLink.<xmlattr>.all",abstract_device.load_shed_availability_list_link.all);
        pt.put("AbstractDevice.LoadShedAvailabilityListLink.<xmlattr>.href",abstract_device.load_shed_availability_list_link.href);
        pt.put("AbstractDevice.LogEventListLink.<xmlattr>.all",abstract_device.log_event_list_link.all);
        pt.put("AbstractDevice.LogEventListLink.<xmlattr>.href",abstract_device.log_event_list_link.href);
        pt.put("AbstractDevice.PowerStatusLink.<xmlattr>.href",abstract_device.power_status_link.href);
        pt.put("AbstractDevice.sFDI",xml::util::Hexify(abstract_device.sfdi));
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt);
    };

    void Parse(const std::string &xml_str, sep::AbstractDevice *abstract_device)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        abstract_device->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("AbstractDevice.<xmlattr>.subscribable", 0)
        );
        abstract_device->href = pt.get<std::string>("AbstractDevice.<xmlattr>.href", "");
        abstract_device->configuration_link.href = pt.get<std::string>("AbstractDevice.ConfigurationLink.<xmlattr>.href", "");
        abstract_device->der_list_link.all = pt.get<uint32_t>("AbstractDevice.DERListLink.<xmlattr>.all", 0);
        abstract_device->der_list_link.href = pt.get<std::string>("AbstractDevice.DERListLink.<xmlattr>.href", "");
        abstract_device->device_category = static_cast<sep::DeviceCategoryType>(
            pt.get<uint32_t>("AbstractDevice.deviceCategory", 0)
        );
        abstract_device->device_information_link.href = pt.get<std::string>("AbstractDevice.DeviceInformationLink.<xmlattr>.href", "");
        abstract_device->device_status_link.href = pt.get<std::string>("AbstractDevice.DeviceStatusLink.<xmlattr>.href", "");
        abstract_device->file_status_link.href = pt.get<std::string>("AbstractDevice.FileStatusLink.<xmlattr>.href", "");
        abstract_device->ip_interface_list_link.all = pt.get<uint32_t>("AbstractDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        abstract_device->ip_interface_list_link.href = pt.get<std::string>("AbstractDevice.IPInterfaceListLink.<xmlattr>.href", "");
        abstract_device->lfdi = xml::util::Dehexify<boost::multiprecision::uint256_t>(pt.get<std::string>("AbstractDevice.lFDI", ""));
        abstract_device->load_shed_availability_list_link.all = pt.get<uint32_t>("AbstractDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        abstract_device->load_shed_availability_list_link.href = pt.get<std::string>("AbstractDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        abstract_device->log_event_list_link.all = pt.get<uint32_t>("AbstractDevice.LogEventListLink.<xmlattr>.all", 0);
        abstract_device->log_event_list_link.href = pt.get<std::string>("AbstractDevice.LogEventListLink.<xmlattr>.href", "");
        abstract_device->power_status_link.href = pt.get<std::string>("AbstractDevice.PowerStatusLink.<xmlattr>.href", "");
        abstract_device->sfdi = xml::util::Dehexify<uint64_t>(pt.get<std::string>("AbstractDevice.sFDI", ""));
    };

    // Active Power
    std::string Serialize(const sep::ActivePower &active_power)
    {
        boost::property_tree::ptree pt;
        pt.put("ActivePower.multiplier", active_power.multiplier);
        pt.put("ActivePower.value", active_power.value);
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt);
    };

    void Parse(const std::string &xml_str, sep::ActivePower *active_power)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        active_power->multiplier = pt.get<sep::PowerOfTenMultiplierType>("ActivePower.multiplier", 0);
        active_power->value = pt.get<int16_t>("ActivePower.value", 0);
    };

     // Flow Reservation Request
    std::string Serialize(const sep::FlowReservationRequest &fr_request)
    {
        boost::property_tree::ptree pt;
        pt.put("FlowReservationRequest.<xmlattr>.href", "http://uri1");
        pt.put("FlowReservationRequest.mRID", xml::util::Hexify(fr_request.mrid));
        pt.put("FlowReservationRequest.description",fr_request.description);
        pt.put("FlowReservationRequest.version", fr_request.version);
        pt.put("FlowReservationRequest.creationTime", fr_request.creation_time);
        pt.put("FlowReservationRequest.durationRequested", fr_request.duration_requested);
        pt.put("FlowReservationRequest.energyRequested.multiplier", fr_request.energy_requested.multiplier);
        pt.put("FlowReservationRequest.energyRequested.value", fr_request.energy_requested.value);
        pt.put("FlowReservationRequest.intervalRequested.duration", fr_request.interval_requested.duration);
        pt.put("FlowReservationRequest.intervalRequested.start", fr_request.interval_requested.start);
        pt.put("FlowReservationRequest.powerRequested.multiplier", fr_request.power_requested.multiplier);
        pt.put("FlowReservationRequest.powerRequested.value", fr_request.power_requested.value);
        pt.put("FlowReservationRequest.RequestStatus.dateTime", fr_request.request_status.datetime);
        pt.put(
            "FlowReservationRequest.RequestStatus.requestStatus", 
            xml::util::ToUnderlyingType(fr_request.request_status.status)
        );
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt);
    };

    void Parse(const std::string &xml_str, sep::FlowReservationRequest *fr_request)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        fr_request->href = pt.get<std::string>("FlowReservationRequest.<xmlattr>.href", "");
        fr_request->mrid = pt.get<sep::MRIDType>("FlowReservationRequest.mRID", 0);
        fr_request->description = pt.get<std::string>("FlowReservationRequest.description", "");
        fr_request->version = pt.get<uint16_t>("FlowReservationRequest.version", 0);
        fr_request->creation_time = pt.get<sep::TimeType>("FlowReservationRequest.creationTime", 0);
        fr_request->duration_requested = pt.get<uint16_t>("FlowReservationRequest.durationRequested", 0);
        fr_request->energy_requested.multiplier = pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.energyRequested.multiplier", 0);
        fr_request->energy_requested.value = pt.get<int64_t>("FlowReservationRequest.energyRequested.value", 0);
        fr_request->interval_requested.duration = pt.get<uint32_t>("FlowReservationRequest.intervalRequested.duration", 0);
        fr_request->interval_requested.start = pt.get<sep::TimeType>("FlowReservationRequest.intervalRequested.start", 0);
        fr_request->power_requested.multiplier =  pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.powerRequested.multiplier", 0);
        fr_request->power_requested.value =  pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.powerRequested.value", 0);
        fr_request->request_status.datetime =   pt.get<sep::TimeType>("FlowReservationRequest.RequestStatus.dateTime", 0);
        fr_request->request_status.status =  static_cast<sep::RequestStatus::Status>(pt.get<uint8_t>("FlowReservationRequest.RequestStatus.requestStatus", 0));
    }

    std::string Serialize(const sep::FlowReservationResponse &fr_response) 
    {
        boost::property_tree::ptree pt;
        pt.put(
            "FlowReservationResponse.<xmlattr>.subscribable", 
             xml::util::ToUnderlyingType(fr_response.subscribable)
        );
        pt.put("FlowReservationResponse.<xmlattr>.replyTo", fr_response.reply_to);
        pt.put(
            "FlowReservationResponse.<xmlattr>.responseRequired", 
             xml::util::Hexify(xml::util::ToUnderlyingType(fr_response.response_required))
        );
        pt.put("FlowReservationResponse.<xmlattr>.href", fr_response.href);
        pt.put("FlowReservationResponse.mRID", xml::util::Hexify(fr_response.mrid));
        pt.put("FlowReservationResponse.description", fr_response.description);
        pt.put("FlowReservationResponse.version", fr_response.version);
        pt.put("FlowReservationResponse.creationTime", fr_response.creation_time);
        pt.put(
            "FlowReservationResponse.EventStatus.currentStatus", 
             xml::util::ToUnderlyingType(fr_response.event_status.current_status)
        );
        pt.put("FlowReservationResponse.EventStatus.dateTime", fr_response.event_status.date_time);
        pt.put("FlowReservationResponse.EventStatus.potentiallySuperseded", fr_response.event_status.potentially_superseded);
        pt.put("FlowReservationResponse.EventStatus.potentiallySupersededTime", fr_response.event_status.potentially_superseded_time);
        pt.put("FlowReservationResponse.EventStatus.reason", fr_response.event_status.reason);
        pt.put("FlowReservationResponse.interval.duration", fr_response.interval.duration);
        pt.put("FlowReservationResponse.interval.start", fr_response.interval.start);
        pt.put("FlowReservationResponse.energyAvailable.multiplier", fr_response.energy_available.multiplier);
        pt.put("FlowReservationResponse.energyAvailable.value", fr_response.energy_available.value);
        pt.put("FlowReservationResponse.powerAvailable.multiplier", fr_response.power_available.multiplier);
        pt.put("FlowReservationResponse.powerAvailable.value", fr_response.power_available.value);
        pt.put("FlowReservationResponse.subject", fr_response.subject);
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt); 
    }
    
    void Parse(const std::string &xml_str, sep::FlowReservationResponse *fr_response) 
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        fr_response->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("FlowReservationResponse.<xmlattr>.subscribable", 0)
        );
        fr_response->reply_to = pt.get<std::string>("FlowReservationResponse.<xmlattr>.replyTo", "");
        fr_response->response_required = static_cast<sep::RespondableResource::ResponseRequired>(
            xml::util::Dehexify<uint8_t>(pt.get<std::string>("FlowReservationResponse.<xmlattr>.responseRequired", "00"))
        );
        fr_response->href = pt.get<std::string>("FlowReservationResponse.<xmlattr>.href", "");
        fr_response->mrid = pt.get<sep::MRIDType>("FlowReservationResponse.mRID", 0);
        fr_response->description = pt.get<std::string>("FlowReservationResponse.description", "");
        fr_response->version = pt.get<uint16_t>("FlowReservationResponse.version", 0);
        fr_response->creation_time = pt.get<uint16_t>("FlowReservationResponse.creationTime", 0);
        fr_response->event_status.current_status = static_cast<sep::CurrentStatus>(
            pt.get<uint8_t>("FlowReservationResponse.EventStatus.currentStatus", 0)
        );
        fr_response->event_status.date_time = pt.get<uint8_t>("FlowReservationResponse.EventStatus.dateTime", 0);
        fr_response->event_status.potentially_superseded = pt.get<bool>("FlowReservationResponse.EventStatus.potentiallySuperseded", false);
        fr_response->event_status.potentially_superseded_time = pt.get<sep::TimeType>("FlowReservationResponse.EventStatus.potentiallySupersededTime", 0);
        fr_response->event_status.reason = pt.get<std::string>("FlowReservationResponse.EventStatus.reason", "");
        fr_response->interval.duration = pt.get<uint32_t>("FlowReservationResponse.interval.duration", 0);
        fr_response->interval.start = pt.get<sep::TimeType>("FlowReservationResponse.interval.start", 0);
        fr_response->energy_available.multiplier = pt.get<uint8_t>("FlowReservationResponse.energyAvailable.multiplier", 0);
        fr_response->energy_available.value = pt.get<int64_t>("FlowReservationResponse.energyAvailable.value", 0);
        fr_response->power_available.multiplier = pt.get<uint8_t>("FlowReservationResponse.powerAvailable.multiplier", 0);
        fr_response->power_available.value = pt.get<int16_t>("FlowReservationResponse.powerAvailable.value", 0);
        fr_response->subject = pt.get<std::string>("FlowReservationResponse.subject", "");
    }
    
    std::string Serialize(const sep::DeviceCapability &dcap) 
    {
        boost::property_tree::ptree pt;
        pt.put("DeviceCapability.<xmlattr>.pollRate", dcap.poll_rate);
        pt.put("DeviceCapability.<xmlattr>.href", dcap.href);
        pt.put("DeviceCapability.CustomerAccountListLink.<xmlattr>.href", dcap.customer_account_list_link.href);
        pt.put("DeviceCapability.CustomerAccountListLink.<xmlattr>.all", dcap.customer_account_list_link.all);
        pt.put("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href", dcap.demand_response_program_list_link.href);
        pt.put("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all", dcap.demand_response_program_list_link.all);
        pt.put("DeviceCapability.DERProgramListLink.<xmlattr>.href", dcap.der_program_list_link.href);
        pt.put("DeviceCapability.DERProgramListLink.<xmlattr>.all", dcap.der_program_list_link.all);
        pt.put("DeviceCapability.FileListLink.<xmlattr>.href", dcap.file_list_link.href);
        pt.put("DeviceCapability.FileListLink.<xmlattr>.all", dcap.file_list_link.all);
        pt.put("DeviceCapability.MessagingProgramListLink.<xmlattr>.href", dcap.messaging_program_list_link.href);
        pt.put("DeviceCapability.MessagingProgramListLink.<xmlattr>.all", dcap.messaging_program_list_link.all);
        pt.put("DeviceCapability.PrepaymentListLink.<xmlattr>.href", dcap.prepayment_list_link.href);
        pt.put("DeviceCapability.PrepaymentListLink.<xmlattr>.all", dcap.prepayment_list_link.all);
        pt.put("DeviceCapability.ResponseSetListLink.<xmlattr>.href", dcap.response_set_list_link.href);
        pt.put("DeviceCapability.ResponseSetListLink.<xmlattr>.all", dcap.response_set_list_link.all);
        pt.put("DeviceCapability.TariffProfileListLink.<xmlattr>.href", dcap.tariff_profile_list_link.href);
        pt.put("DeviceCapability.TariffProfileListLink.<xmlattr>.all", dcap.tariff_profile_list_link.all);
        pt.put("DeviceCapability.TimeLink.<xmlattr>.href", dcap.time_link.href);
        pt.put("DeviceCapability.UsagePointListLink.<xmlattr>.href", dcap.usage_point_list_link.href);
        pt.put("DeviceCapability.UsagePointListLink.<xmlattr>.all", dcap.usage_point_list_link.all);
        pt.put("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href", dcap.mirror_usage_point_list_link.href);
        pt.put("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all", dcap.mirror_usage_point_list_link.all);
        pt.put("DeviceCapability.SelfDeviceLink.<xmlattr>.href", dcap.demand_response_program_list_link.href);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt); 
    }
    
    void Parse(const std::string &xml_str, sep::DeviceCapability *dcap) 
    {

        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        dcap->poll_rate = pt.get<uint32_t>("DeviceCapability.<xmlattr>.pollRate", 900);
        dcap->href = pt.get<std::string>("DeviceCapability.<xmlattr>.href", "");
        dcap->customer_account_list_link.href = pt.get<std::string>("DeviceCapability.CustomerAccountListLink.<xmlattr>.href", "");
        dcap->customer_account_list_link.all = pt.get<uint32_t>("DeviceCapability.CustomerAccountListLink.<xmlattr>.all", 0);
        dcap->demand_response_program_list_link.href = pt.get<std::string>("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.href", "");
        dcap->demand_response_program_list_link.all = pt.get<uint32_t>("DeviceCapability.DemandResponseProgramListLink.<xmlattr>.all", 0);
        dcap->der_program_list_link.href = pt.get<std::string>("DeviceCapability.DERProgramListLink.<xmlattr>.href", "");
        dcap->der_program_list_link.all = pt.get<uint32_t>("DeviceCapability.DERProgramListLink.<xmlattr>.all", 0);
        dcap->file_list_link.href = pt.get<std::string>("DeviceCapability.FileListLink.<xmlattr>.href", "");
        dcap->file_list_link.all = pt.get<uint32_t>("DeviceCapability.FileListLink.<xmlattr>.all", 0);
        dcap->messaging_program_list_link.href = pt.get<std::string>("DeviceCapability.MessagingProgramListLink.<xmlattr>.href", "");
        dcap->messaging_program_list_link.all = pt.get<uint32_t>("DeviceCapability.MessagingProgramListLink.<xmlattr>.all", 0);
        dcap->prepayment_list_link.href = pt.get<std::string>("DeviceCapability.PrepaymentListLink.<xmlattr>.href", "");
        dcap->prepayment_list_link.all = pt.get<uint32_t>("DeviceCapability.PrepaymentListLink.<xmlattr>.all", 0);
        dcap->response_set_list_link.href = pt.get<std::string>("DeviceCapability.ResponseSetListLink.<xmlattr>.href", "");
        dcap->response_set_list_link.all = pt.get<uint32_t>("DeviceCapability.ResponseSetListLink.<xmlattr>.all", 0);
        dcap->tariff_profile_list_link.href = pt.get<std::string>("DeviceCapability.TariffProfileListLink.<xmlattr>.href", "");
        dcap->tariff_profile_list_link.all = pt.get<uint32_t>("DeviceCapability.TariffProfileListLink.<xmlattr>.all", 0);
        dcap->time_link.href = pt.get<std::string>("DeviceCapability.TimeLink.<xmlattr>.href", "");
        dcap->usage_point_list_link.href = pt.get<std::string>("DeviceCapability.UsagePointListLink.<xmlattr>.href", "");
        dcap->usage_point_list_link.all = pt.get<uint32_t>("DeviceCapability.UsagePointListLink.<xmlattr>.all", 0);
        dcap->mirror_usage_point_list_link.href = pt.get<std::string>("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.href", "");
        dcap->mirror_usage_point_list_link.all = pt.get<uint32_t>("DeviceCapability.MirrorUsagePointListLink.<xmlattr>.all", 0);
        dcap->self_device_link.href = pt.get<std::string>("DeviceCapability.SelfDeviceLink.<xmlattr>.href", "");
    }
    
    std::string Serialize(const sep::EndDevice &edev) 
    {
        boost::property_tree::ptree pt;
        pt.put("EndDevice.<xmlattr>.subscribable", xml::util::ToUnderlyingType(edev.subscribable));
        pt.put("EndDevice.<xmlattr>.href", edev.href);
        pt.put("EndDevice.ConfigurationLink.<xmlattr>.href", edev.configuration_link.href);
        pt.put("EndDevice.DERListLink.<xmlattr>.href", edev.der_list_link.href);
        pt.put("EndDevice.DERListLink.<xmlattr>.all", edev.der_list_link.all);
        pt.put("EndDevice.deviceCategory",  xml::util::Hexify(xml::util::ToUnderlyingType(edev.device_category)));
        pt.put("EndDevice.DeviceInformationLink.<xmlattr>.href", edev.device_information_link.href);
        pt.put("EndDevice.DeviceStatusLink.<xmlattr>.href", edev.device_status_link.href);
        pt.put("EndDevice.FileStatusLink.<xmlattr>.href", edev.file_status_link.href);
        pt.put("EndDevice.IPInterfaceListLink.<xmlattr>.href", edev.ip_interface_list_link.href);
        pt.put("EndDevice.IPInterfaceListLink.<xmlattr>.all", edev.ip_interface_list_link.all);
        pt.put("EndDevice.lFDI", edev.lfdi);
        pt.put("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href", edev.load_shed_availability_list_link.href);
        pt.put("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.all", edev.load_shed_availability_list_link.all);
        pt.put("EndDevice.LogEventListLink.<xmlattr>.href", edev.log_event_list_link.href);
        pt.put("EndDevice.LogEventListLink.<xmlattr>.all", edev.log_event_list_link.all);
        pt.put("EndDevice.PowerStatusLink.<xmlattr>.href", edev.power_status_link.href);
        pt.put("EndDevice.sFDI", edev.sfdi);
        pt.put("EndDevice.changedTime", edev.changed_time);
        pt.put("EndDevice.enabled", edev.enabled);
        pt.put("EndDevice.FlowReservationRequestListLink.<xmlattr>.href", edev.flow_reservation_request_list_link.href);
        pt.put("EndDevice.FlowReservationRequestListLink.<xmlattr>.all", edev.flow_reservation_request_list_link.all);
        pt.put("EndDevice.FlowReservationResponseListLink.<xmlattr>.href", edev.flow_reservation_response_list_link.href);
        pt.put("EndDevice.FlowReservationResponseListLink.<xmlattr>.all", edev.flow_reservation_response_list_link.all);
        pt.put("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href", edev.function_set_assignments_list_link.href);
        pt.put("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.all", edev.function_set_assignments_list_link.all);
        pt.put("EndDevice.postRate", edev.post_rate);
        pt.put("EndDevice.RegistrationLink.<xmlattr>.href", edev.registration_link.href);
        pt.put("EndDevice.SubscriptionListLink.<xmlattr>.href", edev.subscription_list_link.href);
        pt.put("EndDevice.SubscriptionListLink.<xmlattr>.all", edev.subscription_list_link.all);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt); 
    }
    
    void Parse(const std::string &xml_str, sep::EndDevice *edev) 
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        edev->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("EndDevice.<xmlattr>.subscribable", 0)
        );
        edev->href = pt.get<std::string>("EndDevice.<xmlattr>.href", "");
        edev->configuration_link.href = pt.get<std::string>("EndDevice.ConfigurationLink.<xmlattr>.href", "");
        edev->der_list_link.href = pt.get<std::string>("EndDevice.DERListLink.<xmlattr>.href", "");
        edev->der_list_link.all = pt.get<uint32_t>("EndDevice.DERListLink.<xmlattr>.all", 0);
        edev->device_category = static_cast<sep::DeviceCategoryType>(
            xml::util::Dehexify<uint32_t>(pt.get<std::string>("EndDevice.deviceCategory", "00"))
        );
        edev->device_information_link.href = pt.get<std::string>("EndDevice.DeviceInformationLink.<xmlattr>.href", "");
        edev->device_status_link.href  = pt.get<std::string>("EndDevice.DeviceStatusLink.<xmlattr>.href", "");
        edev->file_status_link.href  = pt.get<std::string>("EndDevice.FileStatusLink.<xmlattr>.href", "");
        edev->ip_interface_list_link.href  = pt.get<std::string>("EndDevice.IPInterfaceListLink.<xmlattr>.href", "");
        edev->ip_interface_list_link.all = pt.get<uint32_t>("EndDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        edev->lfdi = xml::util::Dehexify<boost::multiprecision::uint256_t>(pt.get<std::string>("EndDevice.lFDI", ""));
        edev->load_shed_availability_list_link.href  = pt.get<std::string>("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        edev->load_shed_availability_list_link.all  = pt.get<uint32_t>("EndDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        edev->log_event_list_link.href  = pt.get<std::string>("EndDevice.LogEventListLink.<xmlattr>.href", "");
        edev->log_event_list_link.all  = pt.get<uint32_t>("EndDevice.LogEventListLink.<xmlattr>.all", 0);
        edev->power_status_link.href  = pt.get<std::string>("EndDevice.PowerStatusLink.<xmlattr>.href", "");
        edev->sfdi = xml::util::Dehexify<uint64_t>(pt.get<std::string>("EndDevice.sFDI", ""));
        edev->changed_time = pt.get<sep::TimeType>("EndDevice.changedTime", 0);
        edev->enabled = pt.get<bool>("EndDevice.enabled", false);
        edev->flow_reservation_request_list_link.href  = pt.get<std::string>("EndDevice.FlowReservationRequestListLink.<xmlattr>.href", "");
        edev->flow_reservation_request_list_link.all  = pt.get<uint32_t>("EndDevice.FlowReservationRequestListLink.<xmlattr>.all", 0);
        edev->flow_reservation_response_list_link.href  = pt.get<std::string>("EndDevice.FlowReservationResponseListLink.<xmlattr>.href", "");
        edev->flow_reservation_response_list_link.all  = pt.get<uint32_t>("EndDevice.FlowReservationResponseListLink.<xmlattr>.all", 0);
        edev->function_set_assignments_list_link.href  = pt.get<std::string>("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.href", "");
        edev->function_set_assignments_list_link.all  = pt.get<uint32_t>("EndDevice.FunctionSetAssignmentsListLink.<xmlattr>.all", 0);
        edev->post_rate = pt.get<uint32_t>("EndDevice.postRate", 0);
        edev->registration_link.href  = pt.get<std::string>("EndDevice.RegistrationLink.<xmlattr>.href", "");
        edev->subscription_list_link.href  = pt.get<std::string>("EndDevice.SubscriptionListLink.<xmlattr>.href", "");
        edev->subscription_list_link.all  = pt.get<uint32_t>("EndDevice.SubscriptionListLink.<xmlattr>.all", 0);
    }
    
    std::string Serialize(const sep::SelfDevice &sdev) 
    {
        boost::property_tree::ptree pt;
        pt.put("SelfDevice.<xmlattr>.pollRate", sdev.poll_rate);
        pt.put("SelfDevice.<xmlattr>.subscribable", xml::util::ToUnderlyingType(sdev.subscribable));
        pt.put("SelfDevice.<xmlattr>.href", sdev.href);
        pt.put("SelfDevice.ConfigurationLink.<xmlattr>.href", sdev.configuration_link.href);
        pt.put("SelfDevice.DERListLink.<xmlattr>.href", sdev.der_list_link.href);
        pt.put("SelfDevice.DERListLink.<xmlattr>.all", sdev.der_list_link.all);
        pt.put("SelfDevice.deviceCategory",  xml::util::Hexify(xml::util::ToUnderlyingType(sdev.device_category)));
        pt.put("SelfDevice.DeviceInformationLink.<xmlattr>.href", sdev.device_information_link.href);
        pt.put("SelfDevice.DeviceStatusLink.<xmlattr>.href", sdev.device_status_link.href);
        pt.put("SelfDevice.FileStatusLink.<xmlattr>.href", sdev.file_status_link.href);
        pt.put("SelfDevice.IPInterfaceListLink.<xmlattr>.href", sdev.ip_interface_list_link.href);
        pt.put("SelfDevice.IPInterfaceListLink.<xmlattr>.all", sdev.ip_interface_list_link.all);
        pt.put("SelfDevice.lFDI", sdev.lfdi);
        pt.put("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href", sdev.load_shed_availability_list_link.href);
        pt.put("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all", sdev.load_shed_availability_list_link.all);
        pt.put("SelfDevice.LogEventListLink.<xmlattr>.href", sdev.log_event_list_link.href);
        pt.put("SelfDevice.LogEventListLink.<xmlattr>.all", sdev.log_event_list_link.all);
        pt.put("SelfDevice.PowerStatusLink.<xmlattr>.href", sdev.power_status_link.href);
        pt.put("SelfDevice.sFDI", sdev.sfdi);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt); 
    }
    
    void Parse(const std::string &xml_str, sep::SelfDevice *sdev) 
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        sdev->poll_rate = pt.get<uint32_t>("SelfDevice.<xmlattr>.pollRate", 900);
        sdev->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("SelfDevice.<xmlattr>.subscribable", 0)
        );
        sdev->href = pt.get<std::string>("SelfDevice.<xmlattr>.href", "");
        sdev->configuration_link.href  = pt.get<std::string>("SelfDevice.ConfigurationLink.<xmlattr>.href", "");
        sdev->der_list_link.href  = pt.get<std::string>("SelfDevice.DERListLink.<xmlattr>.href", "");
        sdev->der_list_link.all  = pt.get<uint32_t>("SelfDevice.DERListLink.<xmlattr>.all", 0);
        sdev->device_category = static_cast<sep::DeviceCategoryType>(
            xml::util::Dehexify<uint32_t>(pt.get<std::string>("SelfDevice.deviceCategory", "00"))
        );
        sdev->device_information_link.href  = pt.get<std::string>("SelfDevice.DeviceInformationLink.<xmlattr>.href", "");
        sdev->device_status_link.href  = pt.get<std::string>("SelfDevice.DeviceStatusLink.<xmlattr>.href", "");
        sdev->file_status_link.href  = pt.get<std::string>("SelfDevice.FileStatusLink.<xmlattr>.href", "");
        sdev->ip_interface_list_link.href  = pt.get<std::string>("SelfDevice.IPInterfaceListLink.<xmlattr>.href", "");
        sdev->ip_interface_list_link.all  = pt.get<uint32_t>("SelfDevice.IPInterfaceListLink.<xmlattr>.all", 0);
        sdev->lfdi = xml::util::Dehexify<boost::multiprecision::uint256_t>(pt.get<std::string>("SelfDevice.lFDI", ""));
        sdev->load_shed_availability_list_link.href  = pt.get<std::string>("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.href", "");
        sdev->load_shed_availability_list_link.all  = pt.get<uint32_t>("SelfDevice.LoadShedAvailabilityListLink.<xmlattr>.all", 0);
        sdev->log_event_list_link.href  = pt.get<std::string>("SelfDevice.LogEventListLink.<xmlattr>.href", "");
        sdev->log_event_list_link.all  = pt.get<uint32_t>("SelfDevice.LogEventListLink.<xmlattr>.all", 0);
        sdev->power_status_link.href  = pt.get<std::string>("SelfDevice.PowerStatusLink.<xmlattr>.href", "");
        sdev->sfdi = xml::util::Dehexify<uint64_t>(pt.get<std::string>("SelfDevice.sFDI", ""));
    }
    
    std::string Serialize(const sep::Time &time) 
    {
        boost::property_tree::ptree pt;
        pt.put("Time.<xmlattr>.pollRate", time.poll_rate);
        pt.put("Time.<xmlattr>.href", time.href);
        pt.put("Time.currentTime", time.current_time);
        pt.put("Time.dstEndTime", time.dst_end_time);
        pt.put("Time.dstOffset", time.dst_offset);
        pt.put("Time.dstStartTime", time.dst_start_time);
        pt.put("Time.localTime", time.local_time);
        pt.put("Time.quality", time.quality);
        pt.put("Time.tzOffset", time.tz_offset);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(pt);
    }
    
    void Parse(const std::string &xml_str, sep::Time *time) 
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        time->poll_rate = pt.get<uint32_t>("Time.<xmlattr>.pollRate", 900);
        time->href = pt.get<std::string>("Time.<xmlattr>.href", "");
        time->current_time = pt.get<sep::TimeType>("Time.currentTime", 0);
        time->dst_end_time = pt.get<sep::TimeType>("Time.dstEndTime", 0);
        time->dst_offset = pt.get<sep::TimeOffsetType>("Time.dstOffset", 0);
        time->dst_start_time = pt.get<sep::TimeType>("Time.dstStartTime", 0);
        time->local_time = pt.get<sep::TimeType>("Time.dstStartTime", 0);
        time->quality = pt.get<uint8_t>("Time.quality", 7);
        time->tz_offset = pt.get<sep::TimeOffsetType>("Time.tzOffset", 7);
    }
};