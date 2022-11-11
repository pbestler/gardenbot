/**
 * @file lightsensor.h
 * @brief Declaration of light sensor.
 *
 * @date 2022-05-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _LIGHTSENSOR_H_
#define _LIGHTSENSOR_H_

#include <chrono>

class StopWatch;

class LightSensor
{
private:
    StopWatch& _daylightWatch;
public:
    LightSensor() = delete;
    LightSensor(const LightSensor&) = delete;
    LightSensor(StopWatch& daylightWatch);
    ~LightSensor();

    std::chrono::seconds getDayDuration();
    void logDaylight();
    void begin();
    void loop();
};

#endif // _LIGHTSENSOR_H_