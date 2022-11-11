/**
 * @file  lightsensor.h
 *
 * @brief Declaration of the LightSensor.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#ifndef _SRC_HAL_SENSORS_LIGHTSENSOR
#define _SRC_HAL_SENSORS_LIGHTSENSOR

#include "runnable.h"
#include "publishing.h"


namespace hal::sensors {

typedef int32_t light_sensor_res_t;

class LightSensor:
    public Runnable,
    public Publisher<light_sensor_res_t>
{
public:
    LightSensor();
    ~LightSensor();
    void run() override;
};

};

#endif /* _SRC_HAL_SENSORS_LIGHTSENSOR */
