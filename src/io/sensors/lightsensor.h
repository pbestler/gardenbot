#include "dashboard.h"
#include <stdint.h>

#pragma once

class LightSensor
{
private:
    int32_t start_of_day;
    int32_t end_of_day;
public:
    LightSensor();
    ~LightSensor();
    int32_t getDayDuration();
    void begin();
    void loop();
};

extern LightSensor LichtSensor;