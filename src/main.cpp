#include <Arduino.h>

#include "LittleFS.h"

#include "WiFiManager.h"
#include "webServer.h"
#include "updater.h"
#include "fetch.h"
#include "configManager.h"
#include "timeSync.h"
#include "dashboard.h"
#include "gardenmanager.h"
#include "TZ.h"

#define BUILTIN_LED 2

static unsigned long last_time = 0;
static int pin_state = 0;

void setup()
{
    Serial.begin(115200);

    // Initialize with log level and log output.

    LittleFS.begin();
    GUI.begin();
    configManager.begin();
    WiFiManager.begin(configManager.data.projectName, 60000UL);
    dash.begin(1000);
    //Gardener.begin();

    timeSync.begin(TZ_Europe_Berlin);

    //Wait for connection
    timeSync.waitForSyncResult(5000);

    if (timeSync.isSynced())
    {
        time_t now = time(nullptr);
        Serial.print(PSTR("Current time in Berlin: "));
        Serial.print(asctime(localtime(&now)));

    }
    else
    {

        Serial.println("Timeout while receiving the time");

    }

    // Set LED to on.
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, LOW);
    last_time = millis();
    Serial.println("test");
}


void loop()
{
    //software interrupts
    WiFiManager.loop();
    updater.loop();
    dash.loop();
    //Gardener.loop();

    unsigned long curr_time = millis();
    if (curr_time - last_time >= 500)
    {
        last_time = curr_time;
        pin_state = pin_state == 0 ? 1 : 0;
        digitalWrite(BUILTIN_LED, pin_state);
    }
}