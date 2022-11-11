/**
 * @file  adci2c.h
 *
 * @brief Definition of the  ADC1115 connected via i2c.
 *
 * @copyright(c) 2022 Peter Bestler
 */
#include "adci2c.h"
#include "ADS1X15.h"

using namespace hal::sensors;


ADC1115::ADC1115(uint8_t address, uint8_t signal_offset = 0u):
    _ads(address),
    _signal_offset(signal_offset)
{
    if (!_ads.isConnected())
    {
        // TODO Error logging and throw.
    }

    _ads.setMode(1);
    _ads.setGain(1);
};

void ADC1115::run()
{
    for (int i = 0; i < 4; i++)
    {
        double value = _ads.toVoltage(_ads.readADC(i));
        publish(std::make_pair((i + _signal_offset), value));
    }
};
