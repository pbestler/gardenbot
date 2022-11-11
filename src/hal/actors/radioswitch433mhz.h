#ifndef _SRC_HAL_ACTORS_RADIOSWITCH433MHZ
#define _SRC_HAL_ACTORS_RADIOSWITCH433MHZ

#include "RCSwitch.h"
#include <array>
#include <bitset>
#include <functional>
#include "runnable.h"

namespace hal::actors
{

constexpr int NR_OF_SOCKETS = 2;

class RadioSwitch433Mhz:
    public Runnable
{
private:
    RCSwitch _radioModule;
    std::array<std::reference_wrapper<bool>, NR_OF_SOCKETS> _valueMap;
    std::bitset<NR_OF_SOCKETS> _switchValuesCache;
public:
    void run() override;
    RadioSwitch433Mhz();
    ~RadioSwitch433Mhz() {};
};

}
#endif /* _SRC_HAL_ACTORS_RADIOSWITCH433MHZ */
