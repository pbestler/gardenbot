
#include "dashboard_pub.h"
#include "dashboard.h"
#include "configManager.h"

#include <stdint.h>

using namespace service;
using namespace hal::sensors;

DashBoardUpdater::DashBoardUpdater(StopWatch& stopWatch):
    _daylightWatch(stopWatch)
{}

/**
 * @brief Frequently tasks.
 */
void DashBoardUpdater::run(void)
{
    //dash.data.NrOfDaylightMinutes = _daylightWatch.getElapsedTime();
}

/**
 * @brief Subscriber interface to retreive the result of a adc measurement.
 *
 * @param result The result of the measurement, including channel id and
 *               already marshalled value..
 */
void DashBoardUpdater::notify(const adc_result_t& result)
{

}

void DashBoardUpdater::notify(const light_sensor_res_t& result)
{
    dash.data.DaylightSensor = result._lumen;

    // Here we fetch the hysteresis sesttings.<
    const auto nightThreshold = configManager.data.daylightsensorThreshold -
            configManager.data.daylightsensorHysteresis;
    const auto dayThreshold = configManager.data.daylightsensorThreshold +
            configManager.data.daylightsensorHysteresis;


    if ((dash.data.DaylightSensor >= dayThreshold) &&
        (dash.data.IsItDay == false))
    {
        _daylightWatch.start();
        dash.data.IsItDay = true;
    }

    if ((dash.data.DaylightSensor < nightThreshold) &&
        (dash.data.IsItDay == true))
    {
        _daylightWatch.stop();
        dash.data.IsItDay = false;
    }
}

void DashBoardUpdater::notify(const hal::sensors::temp_hum_res_t& result)
{

}

void ConditionController::run()
{
    manageArtificialLight();
    manageWaterPump();
    manageDoor();
}

void ConditionController::manageArtificialLight()
{
    time_t curr_time = time(NULL);
    tm *tmLocal = localtime(&curr_time);

    /* We just should switch artificial light after 20:00 o clock.*/
    if (tmLocal->tm_hour <= 19)
    {
        return;
    }

    if ((dash.data.NrOfDaylightMinutes > 0) &&
        (dash.data.NrOfDaylightMinutes < configManager.data.minutesOfLightPerDay) &&
        (dash.data.IsItDay == false) &&
        (dash.data.Socket1 == false))
    {
        dash.data.Socket1 = true;
        digitalWrite(D0, LOW);

    } else if ((dash.data.NrOfDaylightMinutes >= 0) &&
        (dash.data.NrOfDaylightMinutes >= configManager.data.minutesOfLightPerDay) &&
        (dash.data.Socket1 == true))
    {
        dash.data.Socket1 = false;
        digitalWrite(D0, HIGH);
    }
}

void ConditionController::manageWaterPump()
{
    // TODO PBE: Implement me.
}

void ConditionController::manageDoor()
{
    // TODO PBE: Implement me.
}