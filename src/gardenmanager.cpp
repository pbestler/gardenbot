#include "gardenmanager.h"
#include "MyAlarm.h"
#include "LittleFS.h"
#include "dashboard.h"

GardenManager Gardener;

GardenManager::GardenManager():
    _daylightWatch(),
    _lightSensor(_daylightWatch),
    _switches()
{}

void GardenManager::begin()
{
    timerAlarm.startService();
    timerAlarm.createDay(0, 0, 1, [&] () { _daylightWatch.reset(); });
    timerAlarm.createDay(23, 50, 0, [&] () { _lightSensor.logDaylight();});

    // Evaluate io.
    _lightSensor.begin();
    _switches.begin();
}

void GardenManager::loop()
{
    // Evaluate io.
    _lightSensor.loop();
    _switches.loop();

    timerAlarm.update();
}