/**
 * @file lightsensor.h
 * @brief Declaration of light sensor.
 *
 * @date 2022-05-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _SRC_HAL_SENSORS_LIGHTSENSOR
#define _SRC_HAL_SENSORS_LIGHTSENSOR

#include "runnable.h"
#include "publishing.h"


namespace hal::sensors {

typedef struct light_sensor_res
{
    int32_t _lumen;

    explicit light_sensor_res(int32_t val):
        _lumen(val)
    {};
} light_sensor_res_t;


class LightSensor: public Runnable
{
private:
public:
    Publisher<light_sensor_res_t> _lightSensorSubscribers;
    LightSensor();
    ~LightSensor();
    void run() override;

};

};

#endif /* _SRC_HAL_SENSORS_LIGHTSENSOR */
