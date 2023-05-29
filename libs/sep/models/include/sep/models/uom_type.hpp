#ifndef __UOM_TYPE_H__
#define __UOM_TYPE_H__
#include "simple_types.hpp"

namespace sep
{
    // The following values are recommended values sourced from 
    // the unit of measure enumeration in IEC 61968-9 [61968]. 
    // Other values from the unit of measure enumeration in 
    // IEC 61968-9 [61968] MAY be used.
    enum class UomType : UInt8
    {
        kNA,
        kAmpere = 5,
        kKelvin = 6,
        kCelsius = 23,
        kVoltage = 29,
        kJoule = 31,
        kHertz = 33,
        kWatts = 38,
        kCubicMeter = 42,
        kApparentPower = 61,
        kReactivePower = 63,
        kDisplacementPowerFactor = 65,
        kVoltSquared = 67,
        kAmpSqquared = 69,
        kApparentEnergy = 71,
        kRealEnergy = 72,
        kReactiveEnergy = 73,
        kAmpereHours = 106,
        kCubicFeet = 119,
        kCubicFeetPerHour = 122,
        kCubicMeterPerHour = 125,
        kUSGallons = 128,
        kUSGallonsPerHour = 129,
        kImperialGallons = 130,
        kImperialGallonsPerHour = 131,
        kBritishThermalUnits = 132,
        kBritishThermalUnitsPerHour = 133,
        kLiter = 134,
        kLitersPerHour = 137,
        kPAGuage = 140,
        kPAAbsolute = 155,
        kTherm = 169
    };
} // namespace sep

#endif // __UOM_TYPE_H__