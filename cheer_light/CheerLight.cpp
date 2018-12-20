/*
 * CheerLight.cpp
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
#include "CheerLight.h"

using namespace application;
using namespace application::interface;
using namespace driver;
using namespace middleware;

CheerLight CheerLight::_instance;

void CheerLight::setup(void) {
  _ledStrip.begin();
  _ledStrip.setDelay(100);
  _ledStrip.setBrightness(32);
  _ledStrip.setColor(255, 0, 0);
  _pirSensor.init();
  _loudnessSensor.init();

  _pirSensor.addDelegate(&_detectedDelegate);
  _loudnessSensor.addDelegate(&_absoluteLoudnessDelegate);
  _loudnessSensor.addDelegate(&_relativeLoudnessDelegate);
}

void CheerLight::loop(void) {
  if (_animation == 0) {
     _ledStrip.blinking();
  } else if (_animation == 1) {
    _ledStrip.rainbow();
  } else {
    _ledStrip.breathing();
  }
  
  _ledStrip.setBrightness(32);
}

void CheerLight::setPIRSensorPin(uint8_t pin) {
  _pirSensor.setPin(pin);
}

void CheerLight::setLoudnessSensorPin(uint8_t pin) {
  _loudnessSensor.setPin(pin);
}

void CheerLight::measureSensors(void) {
  _pirSensor.measure();
  _loudnessSensor.measure();
}

void CheerLight::changeAnimation(void * args) {
  if (((PIRSensor *)args)->isDetected()) {
    Serial.println("detected");
    
    _animation = (_animation + 1) % 3;
    Serial.print("animation: ");
    Serial.println(_animation);
  }
}

void CheerLight::changeSpeed(void * args) {
  uint16_t loudness = ((LoudnessSensor *)args)->getAbsoluteLoudness();
  
  Serial.print("absolute loudness: ");
  Serial.println(loudness);

  _ledStrip.setDelay(1023 - loudness);
}

void CheerLight::changeColor(void * args) {
  int16_t loudness = ((LoudnessSensor *)args)->getRelativeLoudness();
  
  Serial.print("relative loudness: ");
  Serial.println(loudness);

  if (abs(loudness) < 50) {
    return;
  }

  static uint8_t r = 255;
  static uint8_t g = 0;
  static uint8_t b = 0;

  if (b < 255 && r == 255 && g == 0) {
    b = b + 10;
    if (b == 250) {
      b = 255;
    }
  } else if (b == 255 && r > 0 && g == 0) {
    r = r - 10;
    if (r == 5) {
      r = 0;
    }
  } else if (b == 255 && r == 0 && g < 255) {
    g = g + 10;
    if (g == 250) {
      g = 255;
    }
  } else if (b > 0 && r == 0 && g == 255) {
    b = b - 10;
    if (b == 5) {
      b = 0;
    }
  } else if (b == 0 && r < 255 && g == 0) {
    r = r + 10;
    if (r == 250){
      r = 255;
    }
  } else {
    g = g - 10;
    if (g == 5) {
      g = 0;
    }
  }

  _ledStrip.setColor(r,g,b);
}

CheerLight * CheerLight::getInstance(void) {
  return &_instance;
}

CheerLight::CheerLight(void) 
  : _animation(0), 
  _detectedDelegate(Delegate<CheerLight>(this, &CheerLight::changeAnimation)), 
  _absoluteLoudnessDelegate(Delegate<CheerLight>(this, &CheerLight::changeSpeed)), 
  _relativeLoudnessDelegate(Delegate<CheerLight>(this, &CheerLight::changeColor)) { }
  
