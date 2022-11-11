#include "gardenmanager.h"
#include "MyAlarm.h"
#include "LittleFS.h"
#include "dashboard.h"
#include "configManager.h"
#include <ctime>

GardenManager Gardener;

GardenManager::GardenManager():
    _daylightWatch(),
    _lightSensor(_daylightWatch),
    _switches()
{}

void GardenManager::runLightEvaluationLoop()
{
    time_t curr_time = time(NULL);
    tm *tmLocal = localtime(&curr_time);

    /* We just should switch artificial light after 19 o clock.*/
    if (tmLocal->tm_hour <= 19)
    {
        return;
    }

    if ((dash.data.NrOfDaylightMinutes > 0) &&
        (dash.data.NrOfDaylightMinutes < configManager.data.minutesOfLightPerDay) &&
        (dash.data.IsItDay == false) &&
        (dash.data.Socket2 == false))
    {
        dash.data.Socket2 = true;
        digitalWrite(D0, LOW);

    } else if ((dash.data.NrOfDaylightMinutes >= 0) &&
        (dash.data.NrOfDaylightMinutes >= configManager.data.minutesOfLightPerDay) &&
        (dash.data.Socket2 == true))
    {
        dash.data.Socket2 = false;
        digitalWrite(D0, HIGH);
    }


}

void GardenManager::begin()
{
    timerAlarm.startService();
    timerAlarm.createDay(0, 0, 1, [&] () { _daylightWatch.reset(); });
    timerAlarm.createDay(23, 50, 0, [&] () { _lightSensor.logDaylight();});

    // Evaluate io.
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);

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