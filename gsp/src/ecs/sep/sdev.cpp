#include "include/sep/sdev.hpp"

void generateSelfDevice (const std::string& lfdi)
{
    sep::SelfDevice sdev;
    sdev.subscribable = sep::SubscribableType::kNone;
    sdev.href = "/sdev/" + lfdi;
    sdev.configuration_link.href = "/cfg";
    sdev.der_list_link.all = 0;
    sdev.der_list_link.href = "/der";
    sdev.device_category = sep::DeviceCategoryType::kSmartAppliance;
    sdev.device_information_link.href = "/di";
    sdev.device_status_link.href = "/ds";
    sdev.file_status_link.href = "/fs";
    sdev.ip_interface_list_link.all = 0;
    sdev.ip_interface_list_link.href = "/ns";
    sdev.lfdi = xml::util::Dehexify<sep::HexBinary160>(lfdi);
    sdev.load_shed_availability_list_link.all = 0;
    sdev.load_shed_availability_list_link.href = "/lsl";
    sdev.log_event_list_link.all = 0;
    sdev.log_event_list_link.href = "/lel";
    sdev.power_status_link.href = "/ps";
    sdev.sfdi = xml::util::getSFDI(lfdi);

    AccessModule::Fingerprint fingerprint;
    fingerprint.value = lfdi;

    AccessModule::Subject subject;
    subject.value = lfdi;

    World::getInstance().world.entity()
        .set<sep::SelfDevice>(sdev)
        .set<AccessModule::Fingerprint>(fingerprint)
        .set<AccessModule::Subject>(subject);
};