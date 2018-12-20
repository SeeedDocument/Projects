/*
 * PIRSensor.cpp
 * An OOP driver for Grove - Adjustable PIR Motion Sensor.
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
#include "PIRSensor.h"

using namespace driver;
using namespace driver::interface;
using namespace middleware::interface;

PIRSensor::PIRSensor()
  : _pin(0), _detected(false) { }

bool PIRSensor::init(void) {
  return true;
}

void PIRSensor::measure(void) {
  _detected = digitalRead(_pin);
  invokeAllDelegates();
}

void PIRSensor::setPin(uint8_t pin) {
  _pin = pin;
}

void PIRSensor::addDelegate(IDelegate * delegate) {
  _delegates.push_back(delegate);
}

bool PIRSensor::isDetected(void) {
  return _detected;
}

void PIRSensor::invokeAllDelegates(void) {
  for (uint8_t i = 0; i < _delegates.size(); ++i) {
    _delegates[i]->invoke(this);
  }
}
