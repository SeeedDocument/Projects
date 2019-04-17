#include "ESP8266WiFi.h"
#include "Wire.h"
#include "RtcDS1307.h"

#include "ATT.h"
#include "Display.h"
#include "DrinkingData.h"

#define ULTRASONIC_PIN      ((uint8_t)14)
#define DRINKING_GOAL       ((uint16_t)1000)
#define ALERT_INTERVAL      ((uint8_t)1)

#define WIFI_SSID           ((const char *)"<your_wifi_ssid>")
#define WIFI_PASS           ((const char *)"<your_wifi_password>")

#define ENABLE_GROVE()      \
{                           \
    pinMode(15, OUTPUT);    \
    digitalWrite(15, HIGH); \
}

Display display;
DrinkingData data(ULTRASONIC_PIN);

void setup()
{
    ENABLE_GROVE();
    Serial.begin(9600);

    initRTC();
    initWiFi();

    initATT();
    display.init();
    data.setGoal(DRINKING_GOAL);
    data.setAlertInterval(ALERT_INTERVAL);
}

void loop()
{
    static uint16_t lastProgress = 0;

    data.updateProgress();
    data.updateContinuously();

    display.showDateTime();
    display.showProgress(data.getProgress(), data.getGoal());
    display.showContinuously(data.getContinuously());
    display.showAlert(data.getAlert());

    sendProgress(data.getProgress() - lastProgress);
    lastProgress = data.getProgress();

    delay(100);
}

void initRTC()
{
    RtcDS1307<TwoWire> rtc(Wire);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    rtc.Begin();
    rtc.SetDateTime(compiled);
    rtc.SetIsRunning(true);
}

void initWiFi()
{
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
}
