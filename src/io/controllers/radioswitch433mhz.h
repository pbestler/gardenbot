#pragma once

#include "RCSwitch.h"
#include <array>
#include <bitset>
#include <functional>

constexpr int NR_OF_SOCKETS = 2;

class RadioSwitch433Mhz
{
private:
    RCSwitch _radioModule;
    std::array<std::reference_wrapper<bool>, NR_OF_SOCKETS> _valueMap;
    std::bitset<NR_OF_SOCKETS> _switchValuesCache;
public:
    void begin();
    void loop();
    RadioSwitch433Mhz();
    ~RadioSwitch433Mhz();
};

