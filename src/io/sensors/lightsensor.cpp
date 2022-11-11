
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

AS_BH1750 sensor;

LightSensor::LightSensor(StopWatch& daylightWatch):
    _daylightWatch(daylightWatch)
{

}

LightSensor::~LightSensor()
{

}

std::chrono::seconds LightSensor::getDayDuration()
{
    return this->_daylightWatch.getElapsedTime();
}

void LightSensor::begin()
{

    if(!sensor.begin()) {
        Serial.println("BH1750 init failed!");
        while(true);
    }
}

void LightSensor::loop()
{
    dash.data.DaylightSensor = sensor.readLightLevel();

    if (dash.data.DaylightSensor >= configManager.data.daylightsensorThreshold)
    {
        this->_daylightWatch.start();
        dash.data.IsItDay = true;
    }

    if (dash.data.DaylightSensor < configManager.data.daylightsensorThreshold)
    {
        this->_daylightWatch.stop();
        dash.data.IsItDay = false;
    }
}

