#include <Arduino.h>

#include "gardenmanager.h"

#include <webServer.h>
#include <updater.h>
#include <fetch.h>
#include <timeSync.h>
#include <dashboard.h>
#include <configManager.h>

#include <LittleFS.h>
#include <WiFiManager.h>
#include <TZ.h>

#define BUILTIN_LED 2

static unsigned long last_time = 0;
static int pin_state = 0;

app::GardenManager Gardener;

void setup()
{
    Serial.begin(115200);

    // First of all we enable wifi and get the current time.
    WiFiManager.begin(configManager.data.projectName, 10000UL);
    timeSync.begin(TZ_Europe_Berlin);
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

    // Now we tearup our application.
    LittleFS.begin();
    GUI.begin();
    configManager.begin();
    dash.begin(1000);

    // Set LED to off.
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    last_time = millis();
    Serial.println("Initialization finished.");
}


void loop()
{
    // Software tasks.
    WiFiManager.loop();
    updater.loop();
    dash.loop();
    configManager.loop();
    Gardener.loop();

    // Status LED control.
    unsigned long curr_time = millis();
    if (curr_time - last_time >= 500)
    {
        if (configManager.data.aliveLED == true) {
            last_time = curr_time;
            pin_state = pin_state == 0 ? 1 : 0;
            digitalWrite(BUILTIN_LED, pin_state);
        }
        else
        {
            digitalWrite(BUILTIN_LED, HIGH);
        }
    }
}