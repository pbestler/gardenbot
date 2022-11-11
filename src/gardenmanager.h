#pragma once

#include "lightsensor.h"
#include "radioswitch433mhz.h"

class GardenManager
{

private:
    LightSensor _lightSensor;
    RadioSwitch433Mhz _switches;

    
public:
    GardenManager();
    void begin();
    void loop();
    
};

extern GardenManager Gardener;