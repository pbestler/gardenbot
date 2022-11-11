#include "gardenmanager.h"
#include "MyAlarm.h"
#include "LittleFS.h"
#include "dashboard.h"
#include "configManager.h"

GardenManager Gardener;

GardenManager::GardenManager():
    _daylightWatch(),
    _lightSensor(_daylightWatch),
    _switches()
{}


void GardenManager::runLightEvaluationLoop()
{
    if ((dash.data.NrOfDaylightMinutes > 0) &&
        (dash.data.NrOfDaylightMinutes < configManager.data.minutesOfLightPerDay) &&
        (dash.data.IsItDay == false) &&
        (dash.data.Socket2 == false))
    {
        dash.data.Socket2 = true;
    } else if ((dash.data.NrOfDaylightMinutes >= 0) &&
        (dash.data.NrOfDaylightMinutes >= configManager.data.minutesOfLightPerDay))
    {
        dash.data.Socket2 = false;
    }


}

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
    runLightEvaluationLoop();

}