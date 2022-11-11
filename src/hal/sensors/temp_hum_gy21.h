/**
 * @brief
 *
 *
 */

#ifndef _SRC_HAL_SENSORS_TEMP_HUM_GY21
#define _SRC_HAL_SENSORS_TEMP_HUM_GY21

#include <tuple>

namespace hal::sensors {

typedef enum { humidity = 0, temperature = 1} temp_hum_res_desc_t;
typedef std::pair<double, double> temp_hum_res_t;

}


#endif /* _SRC_HAL_SENSORS_TEMP_HUM_GY21 */
