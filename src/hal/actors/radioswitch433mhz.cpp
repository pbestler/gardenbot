#include "radioswitch433mhz.h"
#include "dashboard.h"
#include "LittleFS.h"

using namespace hal::actors;

enum
{
    ON,
    OFF,
    NR_OF_STATES
};

static int value_to_set[NR_OF_SOCKETS][NR_OF_STATES] = {
                  /* ON     |   OFF */
    /* Socket1 */ {1398084, 1398081},
    /* Scoket2 */ {1397076, 1397073}
};

RadioSwitch433Mhz::RadioSwitch433Mhz():
    _radioModule(),
    _valueMap({dash.data.Socket1, dash.data.Socket2}),
    _switchValuesCache()
{
    _radioModule.enableTransmit(0); //Pin D3
    _radioModule.setProtocol(1);
    _radioModule.setPulseLength(187);

}

void RadioSwitch433Mhz::run()
{
    for (size_t i = 0u; i < this->_valueMap.size(); i++)
    {
        if (this->_valueMap[i].get() != this->_switchValuesCache[i])
        {

            auto file = LittleFS.open("daylight.log", "a+");
            time_t now = time(nullptr);
            std::string timestamp = asctime(localtime(&now));
            timestamp.pop_back();

            file.printf("%s : Switch %i switch from %s => %s.\n", timestamp.c_str(),
                    i, this->_switchValuesCache[i] == true ? "true": "false",
                    this->_valueMap[i].get() == true ? "true": "false");
            file.close();

            //Send the appropriate signal from the lut.
            auto state_index = this->_valueMap[i].get() == true ? ON : OFF;
            _radioModule.send(value_to_set[i][state_index], 24);

            this->_switchValuesCache[i] = this->_valueMap[i].get();
        }
    }
}