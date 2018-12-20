/*
 * cheer_light.ino
 * Main file of Cheer Light project.
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
#include "CheerLight.h"
#include "MsTimer2.h"

using namespace application;
CheerLight * light = CheerLight::getInstance();

void measureSensors() {
  light->measureSensors();
}

void setup() {
  // used for debugging
  Serial.begin(9600);
  while (!Serial);

  // setup PIR Sensor and Loudness Sensor's pin
  light->setPIRSensorPin(2);
  light->setLoudnessSensorPin(A0);

  // setup timer2 interrupt using MsTimer2 library
  MsTimer2::set(2000, measureSensors);
  MsTimer2::start();

  light->setup();
}

void loop() {
  light->loop();
}
