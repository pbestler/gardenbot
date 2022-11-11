
/**
 * @file lightsensor.cpp
 * @author Peter Bestler
 * @brief Implementation of light sensor logic.
 *
 * @date 2022-05-25
 *
 * @copyright Copyright (c) 2022
 *
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

LightSensor::LightSensor():
    _lightSensorSubscribers()
{

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
    _lightSensorSubscribers.publish(light_sensor_res(tmpVal));
}