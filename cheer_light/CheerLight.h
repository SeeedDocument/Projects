/*
 * CheerLight.h
 * Application class of Cheer Light project.
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
#ifndef __CHEERLIGHT_H__
#define __CHEERLIGHT_H__

#include "Delegate.h"
#include "IApplication.h"
#include "LEDStrip.h"
#include "LoudnessSensor.h"
#include "PIRSensor.h"

namespace application {
  class CheerLight;
}

class application::CheerLight
  : public application::interface::IApplication {
public:
  void setup(void);
  void loop(void);

  void setPIRSensorPin(uint8_t pin);
  void setLoudnessSensorPin(uint8_t pin);
  void measureSensors(void);

  void changeAnimation(void * args);
  void changeSpeed(void * args);
  void changeColor(void * args);

  static application::CheerLight * getInstance(void);

protected:
  driver::LEDStrip        _ledStrip;
  driver::PIRSensor       _pirSensor;
  driver::LoudnessSensor  _loudnessSensor;

  uint8_t _animation;

  middleware::Delegate<application::CheerLight> _detectedDelegate;
  middleware::Delegate<application::CheerLight> _absoluteLoudnessDelegate;
  middleware::Delegate<application::CheerLight> _relativeLoudnessDelegate;
  
  CheerLight(void);
  static application::CheerLight _instance;
};

#endif // __CHEERLIGHT_H__
