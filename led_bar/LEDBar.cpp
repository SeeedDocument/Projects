#include "LEDBar.h"

LEDBar::LEDBar(uint8_t clockPin, uint8_t dataPin, uint8_t barCount)
  : _clockPin(clockPin), _dataPin(dataPin), _barCount(barCount), 
  _brightness(0xFF) { }

void LEDBar::begin(void) {
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);
}

void LEDBar::setBits(int bits) {
  for (uint8_t i = 0; i < _barCount; ++i) {
    sendData(0x00);
    
    for (uint8_t j = 0; j < 10; ++j) {
      sendData((bits & 0x01) ? _brightness : 0x00);
      bits >>= 1;
    }

    sendData(0x00);
    sendData(0x00);
  }

  latchData();
}

void LEDBar::setBrightness(uint8_t brightness) {
  _brightness = brightness;
}

void LEDBar::sendData(uint16_t data) {
  uint8_t clk = HIGH;
  
  for (uint8_t i = 0; i < 16; ++i) {
    digitalWrite(_dataPin, (data & 0x8000) ? HIGH : LOW);
    digitalWrite(_clockPin, (clk = !clk));
    data <<= 1;
  }
}

void LEDBar::latchData(void) {
  digitalWrite(_dataPin, LOW);
  delayMicroseconds(10);

  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(_dataPin, HIGH);
    digitalWrite(_dataPin, LOW);
  }
}
