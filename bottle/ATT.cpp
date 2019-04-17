#include "ATT.h"

#define ASSETS_COUNT    ((uint8_t)1)
#define MQTT_SERVER     ((const char *)"api.allthingstalk.io")
#define MQTT_PORT       ((uint16_t)1883)

const char * DEVICE_ID = "<your_device_id>";
const char * DEVICE_TOKEN = "<your_deivce_token>";

ATTDevice device(DEVICE_ID, DEVICE_TOKEN);
CborBuilder payload(device);

WiFiClient espClient;
PubSubClient pubSub(MQTT_SERVER, MQTT_PORT, espClient);

void initATT(void)
{
    Serial.println("Subscribe MQTT");

    while (!device.subscribe(pubSub))
    {
        Serial.println("retrying");
    }
}

void sendProgress(uint16_t progress)
{
    payload.reset();

    payload.map(ASSETS_COUNT);
    payload.addNumber(progress, "Progress");
    
    payload.send();
    device.process();
}
