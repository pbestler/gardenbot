/**
 * @file  lightsensor.cpp
 *
 * @brief  Definition of the LightSensor.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#include "lightsensor.h"
#include "dashboard.h"
#include "configManager.h"
#include <AS_BH1750.h>
#include "stopwatch.h"
#include "LittleFS.h"
#include <string>

#define LOGGING_EN 0

using namespace hal::sensors;

AS_BH1750 sensor;

LightSensor::LightSensor()
{
    if(!sensor.begin()) {
        Serial.println("BH1750 init failed!");
        while(true);
    }
}

LightSensor::~LightSensor()
{}

void LightSensor::run()
{
    int32_t tmpVal = static_cast<int32_t>(sensor.readLightLevel());
    if (tmpVal < 0)
    {
        return;
    }

    // We could read the sensor.
    publish(tmpVal);
}