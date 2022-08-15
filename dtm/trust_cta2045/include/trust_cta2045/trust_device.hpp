#ifndef __TRUST_CTA2045_H__
#define __TRUST_CTA2045_H__

#include <cta2045/abstract_device.hpp>

class TrustCTA2045 : public cta2045::AbstractDevice
{
public:
    TrustCTA2045(/* args */);
    ~TrustCTA2045();

    cta2045::DeviceInfo getDeviceInfo();
    cta2045::commodity_map getCommodity();
    cea2045::ResponseCodes loadUp(const uint8_t duration);
    cea2045::ResponseCodes shed(const uint8_t duration);
    cea2045::ResponseCodes endShed(const uint8_t duration);
    cea2045::ResponseCodes criticalPeakEvent(const uint8_t duration);
    cea2045::ResponseCodes gridEmergency(const uint8_t duration);

private:
    /* data */
};

TrustCTA2045::TrustCTA2045(/* args */)
{
}

TrustCTA2045::~TrustCTA2045()
{
}

#endif // __TRUST_CTA2045_H__