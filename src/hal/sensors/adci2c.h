/**
 * @file adc1115.h
 * @author Peter Bestler
 *
 * @brief
 *
 */
#ifndef _SRC_HAL_SENSORS_ADCI2C
#define _SRC_HAL_SENSORS_ADCI2C

#include "publishing.h"
#include <functional>
#include "runnable.h"
#include <map>
#include <tuple>
#include <stdint.h>

namespace hal::sensors {

/** Declaration of the top which is emitted from ADC. */
typedef std::pair<uint8_t,double> adc_result_t;

class ADC1115:
    public Runnable,
    public Publisher<adc_result_t>
{
    public:
        ADC1115();
        void run() override;
};

}

#endif /* _SRC_HAL_SENSORS_ADCI2C */
