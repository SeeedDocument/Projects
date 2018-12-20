/*
 * LEDStrip.cpp
 * An repacked OOP driver for Grove - Loudness Sensor.
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Yuki ZHU
 * Created Time: Dec 2018
 * Modified Time:
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "LEDStrip.h"

#define __NUMPIXELS 98
#define __PIN       6

using namespace driver;

LEDStrip::LEDStrip(void)
  : _strip(Adafruit_NeoPixel(__NUMPIXELS)) {
  }

void LEDStrip::begin() {
  _strip.begin();
}

void LEDStrip::setDelay(uint8_t delay) {
  _wait = delay;
}

void LEDStrip::setBrightness(uint8_t brightness) {
  _strip.setBrightness(brightness);
}

void LEDStrip::setColor(uint8_t r, uint8_t g, uint8_t b) {
  _color = _strip.Color(r, g, b);  
}

void LEDStrip::rainbow(void) {
  uint16_t i, j;

  for(j = 0; j < 256; j++) {
    for(i = 0; i < _strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel((i + j) & 255));
    }
    _strip.show();
    delay(_wait / 10);
  }
}

//blinking
void LEDStrip::blinking(void) {
  uint8_t i, j, k;
  
  for (i = 0; i < 20; i++) {
    for (i = 0; i < _strip.numPixels(); i++) {
    _strip.setPixelColor(i, _color);
    }
    _strip.show();
    delay(_wait); 
    
    for (i = 0; i < _strip.numPixels(); i++) {
    _strip.setPixelColor(i, 0);
    }
    _strip.show();
    delay(_wait);
  }
}

//breathing
void LEDStrip::breathing(void) {
  uint8_t i, j, k;
  for (j = 0; j < 100; ++j) {
    _strip.setBrightness(j);
    for (i = 0; i < _strip.numPixels(); ++i) {
      _strip.setPixelColor(i, _color); 
    }
    
    _strip.show();
    delay(_wait / 10);
  }
  
  for (j = 100; j > 0; j--) {
    _strip.setBrightness(j);
    for (i = 0; i < _strip.numPixels(); ++i) {
      _strip.setPixelColor(i, _color); 
    }
    
    _strip.show();
    delay(_wait / 10);
  }
}

// Input a value 0 to 255 to get a _strip.color value.
// The colours are a transition r - g - b - back to r.
uint32_t LEDStrip::wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
