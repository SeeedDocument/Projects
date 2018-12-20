/*
 * LEDStrip.h
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


#ifndef __LEDSTRIP_H__
#define __LEDSTRIP_H__

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "ISensor.h"

namespace driver {
  class LEDStrip;
}

class driver::LEDStrip {
public: 

  LEDStrip(void);

  void begin();
  void setDelay(uint8_t delay);
  void setBrightness(uint8_t brightness);
  void setColor(uint8_t r, uint8_t g, uint8_t b);

  void rainbow(void);
  void blinking(void);
  void breathing(void);

protected:
  Adafruit_NeoPixel _strip;
  
  uint32_t _color;
  uint16_t _wait;
  
  uint32_t wheel(byte WheelPos);
};


#endif // __LEDSTRIP_H__
