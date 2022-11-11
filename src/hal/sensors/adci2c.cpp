/**
 * @file  adci2c.h
 *
 * @brief Definition of the  ADC1115 connected via i2c.
 *
 * @copyright(c) 2022 Peter Bestler
 */
#include "adci2c.h"

using namespace hal::sensors;


ADC1115::ADC1115(void)
{};

void ADC1115::run()
{
    double value;

    for (int i = 0; i < 4; i++)
    {
        publish(std::make_pair(i, value));
    }
};
