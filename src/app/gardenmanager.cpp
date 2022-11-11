/**
 * @file  gardenmanager.cpp
 *
 * @brief Definition of the GardenManager.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#include "gardenmanager.h"
#include "dashboard_pub.h"

#include <configManager.h>

#include <MyAlarm.h>
#include <LittleFS.h>
#include <ctime>

using namespace app;

GardenManager::GardenManager():
    _lightSensor(),
    _adc(0x48, 0),
    _daylightWatch(),
    _dashboardUpdater(_daylightWatch),
    _environmentController(),
    _radioSwitch(),
    _sensors(),
    _actors()
{

    /* 1) Connect all subscribers to their corresponding publishers. */
    _lightSensor.addSubscriber(_dashboardUpdater);
    _adc.addSubscriber(_dashboardUpdater);
    _tempHumiditySensor.addSubscriber(_dashboardUpdater);


    /* 2) Add accquiring inputs */
    _sensors.add(_lightSensor);
    _sensors.add(_adc);
    _sensors.add(_tempHumiditySensor);

    /* 3) Add calculation of state model */
    _services.add(_dashboardUpdater);
    _services.add(_environmentController);

    /* 4) Add acttors */
    _actors.add(_radioSwitch);

    /* 5) Setup our cronjobs. */
    timerAlarm.startService();
    timerAlarm.createDay(0, 0, 1, [&] () { _daylightWatch.reset(); });

    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
}

void GardenManager::loop()
{

    /* 1) Accquire input */
    _sensors.run();

    /* 2) Update model and evaluate ruleset */
    _services.run();

    /* 3) Drive outputs */
    _actors.run();

    /* 4) Check chronjobs Async actions. */
    timerAlarm.update();
}