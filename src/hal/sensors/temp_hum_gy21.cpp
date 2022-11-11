/**
 * @file  temp_hum_gy21.cpp
 *
 * @brief Definition of the TempHumSensor.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#include "temp_hum_gy21.h"

#include <SHT2x.h>

using namespace hal::sensors;

SHT21 sht;

TempHumSensor::TempHumSensor(void)
{
    sht.begin();
}

void TempHumSensor::run(void)
{
    if (sht.isConnected())
    {
        sht.read();

        float temperature = sht.getTemperature();
        float humidity = sht.getHumidity();

        publish(std::make_pair(humidity, temperature));
    }
}