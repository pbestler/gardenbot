#include "gardenmanager.h"

GardenManager Gardener;

GardenManager::GardenManager():
    _daylightWatch(),
    _lightSensor(_daylightWatch),
    _switches()
{}

void GardenManager::begin()
{
    // Evaluate io.
    this->_lightSensor.begin();
    this->_switches.begin();
}

void GardenManager::loop()
{
    // Evaluate io.
    this->_lightSensor.loop();
    this->_switches.loop();

    // Do the daylight logic.

}