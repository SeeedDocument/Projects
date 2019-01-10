#ifndef __LEDBAR_H__
#define __LEDBAR_H__

#include "Arduino.h"

class LEDBar {
public:
  LEDBar(uint8_t clockPin, uint8_t dataPin, uint8_t barCount = 1);

  void begin(void);
  void setBits(int bits);
  void setBrightness(uint8_t brightness);
  
private:
  uint8_t _clockPin;
  uint8_t _dataPin;
  uint8_t _barCount;
  
  uint8_t _brightness;

  void latchData(void);
  void sendData(uint16_t data);
};

#endif // __LEDBAR_H__
