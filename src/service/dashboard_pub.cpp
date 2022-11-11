/**
 * @file  dashboard_pub.cpp
 *
 * @brief Implements bussiness logic of our smartgarden, the
 *        dashboard is updated according to the reported values.
 *
 *        In a second step the condition controller checks if there
 *        is an action required.
 *
 *        TODO PBE: If it comes more complex we can split up this file
 *        into multiple and add other services (e.g sending mails, telegram,
 *        pushing to an mqtt broker and so on.)
 *
 *        Fruthermore the dashboard updater is the perfect spot to inject
 *        aspects of signal processing like:
 *           - debouncing of signals
 *           - hysteresis
 *           - convert signals
 *           - marshal signals.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
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
    dash.data.NrOfDaylightMinutes = std::chrono::duration_cast<std::chrono::minutes>(_daylightWatch.getElapsedTime()).count();
}

/**
 * @brief Subscriber interface to retreive the result of a adc measurement.
 *
 * @param result The result of the measurement, including channel id and
 *               already marshalled value..
 */
void DashBoardUpdater::notify(const adc_result_t& result)
{
    std::array<int32_t* const, 1> LUT_FLOAT = {
        &dash.data.MoistureLevel1
    };

    const auto id = std::get<adc_result_desc_t::ID>(result);
    const auto value = std::get<adc_result_desc_t::VALUE>(result);
    if (id < LUT_FLOAT.size())
    {
        *LUT_FLOAT[id] = convertVoltageToMoistureLevel(value);
    }
}

void DashBoardUpdater::notify(const light_sensor_res_t& result)
{
    dash.data.DaylightSensor = result;

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
    // We just forward it to the dashboard.
    dash.data.airTemp = std::get<hal::sensors::temp_hum_res_desc_t::temperature>(result);
    dash.data.airHum = std::get<hal::sensors::temp_hum_res_desc_t::humidity>(result);
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

int32_t service::convertVoltageToMoistureLevel(int32_t voltage)
{
    return map(voltage, 14800, 31000, 100, 0);
}