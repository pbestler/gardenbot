#ifndef _GARDENMANAGER_H_
#define _GARDENMANAGER_H_


#include "lightsensor.h"
#include "radioswitch433mhz.h"
#include "stopwatch.h"

class GardenManager
{

private:
    StopWatch _daylightWatch;
    LightSensor _lightSensor;
    RadioSwitch433Mhz _switches;

    void runLightEvaluationLoop();

public:
    GardenManager();
    void begin();
    void loop();
};

extern GardenManager Gardener;

#endif // _GARDENMANAGER_H_