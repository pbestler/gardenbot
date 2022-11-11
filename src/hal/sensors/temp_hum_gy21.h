/**
 * @file  temp_hum_gy21.h
 *
 * @brief Declaration of the TempHumSensor.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#ifndef _SRC_HAL_SENSORS_TEMP_HUM_GY21
#define _SRC_HAL_SENSORS_TEMP_HUM_GY21

#include <runnable.h>
#include <publishing.h>

#include <tuple>

namespace hal::sensors {

typedef enum { humidity = 0, temperature = 1} temp_hum_res_desc_t;
typedef std::pair<double, double> temp_hum_res_t;


class TempHumSensor:
    public Runnable,
    public Publisher<temp_hum_res_t>
{
    public:
        void run(void) override;
};

}
#endif /* _SRC_HAL_SENSORS_TEMP_HUM_GY21 */
