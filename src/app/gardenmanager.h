/**
 * @file  gardenmanager.h
 *
 * @brief Declaration of the GardenManager.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#ifndef _SRC_APP_GARDENMANAGER
#define _SRC_APP_GARDENMANAGER

#include "adci2c.h"
#include "lightsensor.h"
#include "dashboard_pub.h"
#include "runnable.h"
#include "radioswitch433mhz.h"

namespace app {

class GardenManager
{
private:
    hal::sensors::LightSensor _lightSensor;
    hal::sensors::ADC1115 _adc;
    hal::sensors::TempHumSensor _tempHumiditySensor;
    StopWatch _daylightWatch;
    service::DashBoardUpdater _dashboardUpdater;
    service::ConditionController _environmentController;
    hal::actors::RadioSwitch433Mhz _radioSwitch;

    RunnableContainer _sensors;
    RunnableContainer _services;
    RunnableContainer _actors;

public:
    GardenManager();
    void loop();
};

}
#endif /* _SRC_APP_GARDENMANAGER */
