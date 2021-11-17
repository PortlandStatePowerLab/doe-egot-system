#ifndef __DER_STATUS_H__
#define __DER_STATUS_H__
#include "subscribable_resource.hpp"
#include "connect_status_type.hpp"
#include "inverter_status_type.hpp"
#include "local_control_mode_status_type.hpp"
#include "manufacturer_status_type.hpp"
#include "operational_mode_status_type.hpp"
#include "state_of_charge_status_type.hpp"
#include "storage_mode_status_type.hpp"

namespace sep
{
    struct DERStatus : SubscribableResource
    {
        enum class AlarmStatus : uint32_t
        {
            kOverCurrent = 0 << 1,
            kOverVoltage = 0 << 2,
            kUnderVoltage = 0 << 3, 
            kOverFrequency = 0 << 4,
            kUnderFrequency = 0 << 5,
            kVoltageImbalance = 0 << 6,
            kCurrentImbalance = 0 << 7,
            kEmergencyLocal = 0 << 8,
            kEmergencyRemote = 0 << 9,
            kLowPowerInput = 0 << 10,
            kPhaseRotation = 0 << 11
        };

        AlarmStatus alarm_status;
        ConnectStatusType gen_connection_status;
        InverterStatusType inverter_status;
        LocalControlModeStatusType local_control_mode_status;
        ManufacturerStatusType manufacturer_status;
        OperationalModeStatusType operational_mode_status;
        TimeType reading_time;
        StateOfChargeStatusType state_of_charge_status;
        StorageModeStatusType storageModeStatus;
        ConnectStatusType stor_connect_status;

    };
    
} // namespace sep

#endif // __DER_STATUS_H__