/**
 * @brief
 *
 *
 */

#ifndef _SRC_HAL_SENSORS_TEMP_HUM_GY21
#define _SRC_HAL_SENSORS_TEMP_HUM_GY21

namespace hal::sensors {

typedef struct temp_hum_res {
    double humidity;
    double temperature;
} temp_hum_res_t;

}


#endif /* _SRC_HAL_SENSORS_TEMP_HUM_GY21 */
