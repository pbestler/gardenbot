#include "lightsensor.h"
#include "dashboard.h"
#include "configManager.h"
#include <AS_BH1750.h>

AS_BH1750 sensor;

LightSensor LichtSensor;

LightSensor::LightSensor():
    start_of_day(-1),
    end_of_day(-1)
{

}

LightSensor::~LightSensor()
{

}

int32_t LightSensor::getDayDuration()
{
    return (this->end_of_day - this->start_of_day);
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

    if ((dash.data.DaylightSensor >= configManager.data.daylightsensorThreshold) &&
       (this->start_of_day == -1))
    {
        time_t now = time(nullptr);
        this->start_of_day = (now / 60) % 1440;
        Serial.println("Start of day is:");
        Serial.println(this->start_of_day);
    } 
     
    if ((dash.data.DaylightSensor < configManager.data.daylightsensorThreshold) &&
        (this->start_of_day != -1) && 
        (this->end_of_day == -1))
    {
        time_t now = time(nullptr);
        this->end_of_day = (now / 60) % 1440;
        
        Serial.println("End of day is:");
        Serial.println(this->end_of_day);
        
    }

    // TODO reset on day change.

    dash.data.NrOfDaylightMinutes = this->end_of_day - this->start_of_day;

    
}

