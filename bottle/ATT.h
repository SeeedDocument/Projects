#ifndef __ATT_H__
#define __ATT_H__

#include "Arduino.h"
#include "ATT_IOT.h"
#include "CborBuilder.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

void initATT(void);
void sendProgress(uint16_t progress);

#endif // __ATT_H__
