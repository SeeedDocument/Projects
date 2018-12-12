/*
 * DustSensor.cpp
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
#include "DustSensor.h"

#define __PM1   ((uint8_t)4)
#define __PM25  ((uint8_t)5)
#define __PM10  ((uint8_t)6)

using namespace driver;
using namespace driver::interface;

bool DustSensor::init(void) {
  return !_hm330x.init();
}

void DustSensor::measure(void) {
  _hm330x.read_sensor_value(_buffer, DUST_SENSOR_BUF_SIZE);
  
  if (checkSum()) {
    _pm1 = getResult(__PM1);
    _pm25 = getResult(__PM25);
    _pm10 = getResult(__PM10);
  }
}

uint16_t DustSensor::getPM1(void) {
  return _pm1;
}

uint16_t DustSensor::getPM25(void) {
  return _pm25;
}

uint16_t DustSensor::getPM10(void) {
  return _pm10;
}

bool DustSensor::checkSum(void) {
  uint8_t sum = 0;

  for (uint8_t i = 0; i < DUST_SENSOR_BUF_SIZE - 1; i++) {
    sum += _buffer[i];
  }

  if (sum != _buffer[DUST_SENSOR_BUF_SIZE - 1]) {
    return false;
  }

  return true;
}

uint16_t DustSensor::getResult(uint8_t pm) {
  return (uint16_t)_buffer[pm * 2] << 8 | _buffer[pm * 2 + 1];
}
