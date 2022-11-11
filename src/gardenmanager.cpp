#include "gardenmanager.h"

GardenManager Gardener;

GardenManager::GardenManager():
    _lightSensor(),
    _switches()
{}

void GardenManager::begin()
{
    this->_lightSensor.begin();
    this->_switches.begin();
}

 
void GardenManager::loop()
{
    this->_lightSensor.loop();
    this->_switches.loop();
}