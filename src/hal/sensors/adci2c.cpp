/**
 * @file adc1115.cpp
 *
 * @brief Declaration of the logic for the I2C attached adc1115.cpp
 *
 */
#include "adci2c.h"

using namespace hal::sensors;


ADC1115::ADC1115(void):
    _adcSubscribers()
{
};

void ADC1115::run()
{
    double value;

    for (int i = 0; i < 4; i++)
    {
        _adcSubscribers.publish(adc_result(i, value));
    }
};
