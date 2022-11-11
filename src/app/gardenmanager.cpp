#include "gardenmanager.h"
#include "MyAlarm.h"
#include "LittleFS.h"
#include "dashboard_pub.h"
#include "configManager.h"
#include <ctime>

using namespace app;
using namespace hal::sensors;

GardenManager::GardenManager():
    _lightSensor(),
    _adc(),
    _daylightWatch(),
    _dashboardUpdater(_daylightWatch),
    _environmentController(),
    _radioSwitch(),
    _sensors(),
    _actors()
{

    /* 1) Connect all subscribers to their corresponding publishers. */
    _lightSensor._lightSensorSubscribers.addSubscriber(_dashboardUpdater);
    _adc._adcSubscribers.addSubscriber(_dashboardUpdater);


    /* 2) Add all cyclic tasks to our mainloop (accquisition, evaluation, actors) */
    _sensors.add(_lightSensor);
    _sensors.add(_adc);

    _services.add(_dashboardUpdater);
    _services.add(_environmentController);

    _actors.add(_radioSwitch);

    /* 3) Setup our cronjobs. */
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