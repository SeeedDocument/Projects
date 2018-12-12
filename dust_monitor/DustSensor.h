/*
 * DustSensor.h
 * An repacked OOP driver for Grove - Laser PM2.5 Sensor (HM3301).
 *
 * Copyright (c) 2018 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Lets Blu
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
#ifndef __DUSTSENSOR_H__
#define __DUSTSENSOR_H__

#include "Arduino.h"
#include "Seeed_HM330X.h"

#include "ISensor.h"

#define DUST_SENSOR_BUF_SIZE 29

namespace driver {
  class DustSensor;
}

class driver::DustSensor
  : public driver::interface::ISensor {
public:
  bool init(void);
  void measure(void);

  uint16_t getPM1(void);
  uint16_t getPM25(void);
  uint16_t getPM10(void);

protected:
  HM330X    _hm330x;
  uint16_t  _pm1, _pm25, _pm10;
  uint8_t   _buffer[DUST_SENSOR_BUF_SIZE];
  
  bool checkSum(void);
  uint16_t getResult(uint8_t pm);
};

#endif // __DUSTSENSOR_H__
