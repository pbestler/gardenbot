
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

    // Here we fetch the hysteresis sesttings.<
    const auto nightThreshold = configManager.data.daylightsensorThreshold -
            configManager.data.daylightsensorHysteresis;
    const auto dayThreshold = configManager.data.daylightsensorThreshold +
            configManager.data.daylightsensorHysteresis;


    if ((dash.data.DaylightSensor >= dayThreshold) &&
        (dash.data.IsItDay == false))
    {
        this->_daylightWatch.start();
        auto file = LittleFS.open("daylight.log", "a+");
        time_t now = time(nullptr);
        std::string timestamp = asctime(localtime(&now));
        timestamp.pop_back();
        file.printf("%s : Daylight detected (%i lux)\n", timestamp.c_str(), dash.data.DaylightSensor);
        dash.data.IsItDay = true;
    }

    if ((dash.data.DaylightSensor < nightThreshold) &&
        (dash.data.IsItDay == true))
    {
        this->_daylightWatch.stop();
        auto file = LittleFS.open("daylight.log", "a+");
        time_t now = time(nullptr);
        std::string timestamp = asctime(localtime(&now));
        timestamp.pop_back();
        file.printf("%s : Night detected (%i lux) \n", timestamp.c_str(), dash.data.DaylightSensor);
        dash.data.IsItDay = false;
    }

    dash.data.NrOfDaylightMinutes = std::chrono::duration_cast<std::chrono::minutes>(_daylightWatch.getElapsedTime()).count();
}

