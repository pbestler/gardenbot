## Project goal

The aim of this project is to provide software for esp8266 based sensorboard to recognize and control the environment for growing
herbs on the window sill or balcony.

The smart combination of sensors and actors with a configurable ruleset should not replace the natural environment. It should just support
it. For example some artificial light should be just added if the natural daylight becomes to short, or if rain isn't sufficient water should be added.

Furthermore this project should support my plants if I am on longer holidays.

### System Architecture

#### 1) Sensors

For main systembus to connect sensors I2C was selected. The I2C interface is exposed to 4 4-PIN-Molex-Sockets where different sensors can
be attached. Furthermore an ADS1115 ADC is attached to the I2C, and the 4 ADC-Channels are exposed again with 4 3-PIN-Molex-Sockets.

#### 2) Actors

As actors currently just 433 MHz sockets are supported where. Later on a relayboard could be added to support actors with 12 Volt.

#### 3) Configuration

The configuration of the project by the user should be done via web interface. This is already integrated with the ESP8266 IoT Framework.
Currently the attached sensors are hard coded but this can be in future configurable aswell.

### Software Architecture

For software I selected an 3-Tier approach and integrated it with the ESP8266 IoT Framework (https://github.com/maakbaas/esp8266-iot-framework). Thanks to the awesome work. The framework serves already a neat webapp including onboarding into WiFi, OTA and
a certificate store. Currently the smargarden is just available 'on premisis' not connected to the intnet/cloud.

For accessing the sensors I utilized the manyfold libraries from the community.

The two basic software architecture patterns are publish/subscribe and runnable modules. The application is single threaded and runs in a synchronous manner. For supporting 'cronjobs' I utilized the MyAlarm. I tried to stick to common aggreed software principles like (DRY, YAGNI, RAII, DI, SOLID and so on).

### Todos & Backlog.
    - [ ] #QA# Currently logging is still missing.
    - [ ] #QA# Add some unit test with gtest.
    - [ ] #Hardware# Add documentation regarding the hardware and design and print a PCB including a small BOM with links.
    - [ ] #Feature# Add integration to HomeAssistant / Cloud including provisioning service with a 'DeviceTree'



