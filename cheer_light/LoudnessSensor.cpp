/*
 * LoudnessSensor.cpp
 * An OOP driver for Grove - Loudness Sensor.
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
#include "LoudnessSensor.h"

using namespace driver;
using namespace driver::interface;
using namespace middleware::interface;

LoudnessSensor::LoudnessSensor(void)
  : _pin(0), _absoluteLoudness(0), _relativeLoudness(0) { }


bool LoudnessSensor::init(void) {
  return true;
}

void LoudnessSensor::measure(void) {
  uint16_t loudness = analogRead(_pin);
  
  _relativeLoudness = loudness - _absoluteLoudness;
  _absoluteLoudness = loudness;
  
  invokeAllDelegates();
}

void LoudnessSensor::setPin(uint8_t pin) {
  _pin = pin;  
}

void LoudnessSensor::addDelegate(IDelegate * delegate) {
  _delegates.push_back(delegate);
}

uint16_t LoudnessSensor::getAbsoluteLoudness(void) {
  return _absoluteLoudness;
}

int16_t LoudnessSensor::getRelativeLoudness(void) {
  return _relativeLoudness;
}

void LoudnessSensor::invokeAllDelegates(void) {
  for (uint8_t i = 0; i < _delegates.size(); ++i) {
    _delegates[i]->invoke(this);
  }
}
