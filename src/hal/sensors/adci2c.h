/**
 * @file  adci2c.h
 *
 * @brief Declaration ADC1115 connected via i2c.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#ifndef _SRC_HAL_SENSORS_ADCI2C
#define _SRC_HAL_SENSORS_ADCI2C

#include "publishing.h"
#include <functional>
#include "runnable.h"
#include <map>
#include <tuple>
#include <stdint.h>
#include "ADS1X15.h"

namespace hal::sensors {

typedef enum { ID = 0, VALUE = 1} adc_result_desc_t;
/** Declaration of the top which is emitted from ADC. */
typedef std::pair<uint8_t,int32_t> adc_result_t;

class ADC1115:
    public Runnable,
    public Publisher<adc_result_t>
{
    public:
        explicit ADC1115(uint8_t address, uint8_t signal_offset);
        void run() override;

    private:
        ADS1115 _ads;
        uint8_t _signal_offset;
};

}

#endif /* _SRC_HAL_SENSORS_ADCI2C */
