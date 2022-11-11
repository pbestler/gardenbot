
#ifndef _SRC_SERVICE_DASHBOARD_PUB
#define _SRC_SERVICE_DASHBOARD_PUB

#include "adci2c.h"
#include "lightsensor.h"
#include "temp_hum_gy21.h"
#include "stopwatch.h"
#include <publishing.h>
#include "runnable.h"

namespace service
{
    /**
     * @brief This updates our model.
     */
    class DashBoardUpdater:
            public Runnable,
            public Subscriber<hal::sensors::adc_result_t>,
            public Subscriber<hal::sensors::light_sensor_res_t>,
            public Subscriber<hal::sensors::temp_hum_res_t>
    {

        public:
            /**
             * @brief Sink for adc results.
             */
            void notify(const hal::sensors::adc_result_t& result) override;

            /**
             * @brief Sink for daylight status
             */
            void notify(const hal::sensors::light_sensor_res_t& result) override;

            /**
             * @brief Sink of the air humidity and temperature results.
             */
            void notify(const hal::sensors::temp_hum_res_t& result) override;

            /*
             * Frequently update of dashboard.
             */
            void run(void) override;

            DashBoardUpdater(StopWatch& stopWatch);

        private:
            StopWatch& _daylightWatch;
    };

    /**
     * This class controlls the environment of our garden.
     *
     * It implements the ruleset of the garden:
     *     - When additional light should be added.
     *     - When the plants should be watered.
     *     - When the door should be closed or opened.
     *     - When the fan should be turned on.
     */
    class ConditionController:
        public Runnable
    {
        public:
            void run(void) override;

        private:

            void manageArtificialLight(void);
            void manageWaterPump(void);
            void manageDoor(void);
    };

    /**
     * @brief Marshalling function to convert read in adc values into soil moisture values.
     *
     * @return double The moisture level in percentage.
     */
    double convertVoltageToMoistureLevel(double voltage);
};


#endif /* _SRC_SERVICE_DASHBOARD_PUB */
