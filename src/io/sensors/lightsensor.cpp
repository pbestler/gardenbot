
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

void LightSensor::logDaylight()
{
    auto file = LittleFS.open("daylight.log", "a+");
    time_t now = time(nullptr);
    std::string timestamp = asctime(localtime(&now));
    timestamp.pop_back();

    file.printf("%s : Today daylight was %i minutes.\n", timestamp.c_str(),
            dash.data.NrOfDaylightMinutes);
    file.close();
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

    dash.data.NrOfDaylightMinutes = std::chrono::duration_cast<std::chrono::minutes>(_daylightWatch.getElapsedTime()).count();
}

