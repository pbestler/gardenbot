#include "radioswitch433mhz.h"
#include "dashboard.h"

RadioSwitch433Mhz::RadioSwitch433Mhz():
    _radioModule(),
    _valueMap({dash.data.Socket1, dash.data.Socket2}),
    _switchValuesCache()
{
    _radioModule.enableTransmit(10);
}

RadioSwitch433Mhz::~RadioSwitch433Mhz()
{}

void RadioSwitch433Mhz::begin()
{
}

void RadioSwitch433Mhz::loop()
{
    for (size_t i = 0u; i < this->_valueMap.size(); i++)
    {   
        if (this->_valueMap[i].get() != this->_switchValuesCache[i])
        {
            Serial.printf("Socket %i switch from %s => %s \n", 
                    i,
                    this->_switchValuesCache[i] == true ? "true": "false",
                    this->_valueMap[i].get() == true ? "true": "false");
            this->_switchValuesCache[i] = this->_valueMap[i].get();
        }
    }
}