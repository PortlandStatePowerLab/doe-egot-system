#include "include/sep/dcap.hpp"

void generateDeviceCapabilities ()
{
    sep::DeviceCapability dcap;
    dcap.poll_rate = 900;
    dcap.href = "/dcap";
    dcap.der_program_list_link.all = 0;
    dcap.der_program_list_link.href = "/derp";
    dcap.response_set_list_link.all = 0;
    dcap.response_set_list_link.href = "/rsps";
    dcap.time_link.href = "/tm";
    dcap.end_device_list_link.all = 0;
    dcap.end_device_list_link.href = "/edev";
    dcap.self_device_link.href = "/sdev";

    World::getInstance().world.entity().set<sep::DeviceCapability>(dcap);
};