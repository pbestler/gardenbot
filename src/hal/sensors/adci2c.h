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
#include <stdint.h>

namespace hal::sensors {

/** Declaration of the top which is emitted from ADC. */
struct adc_result{
    uint32_t _channelId;
    double _value;

    adc_result(uint32_t channel, double val):
        _channelId(channel),
        _value(val)
    {};
};

typedef adc_result adc_result_t;

class ADC1115:
    public Runnable
{

    public:
        ADC1115();
        void run() override;
        Publisher<adc_result_t> _adcSubscribers;
};

}

#endif /* _SRC_HAL_SENSORS_ADCI2C */
