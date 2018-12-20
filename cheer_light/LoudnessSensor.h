/*
 * LoudnessSensor.h
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
#ifndef __LOUDNESSSENSOR_H__
#define __LOUDNESSSENSOR_H__

#include "IDelegate.h"
#include "ISensor.h"
#include "Vector.h"

namespace driver {
  class LoudnessSensor;
}

class driver::LoudnessSensor
  : public driver::interface::ISensor {
public:
  LoudnessSensor(void);

  bool init(void);
  void measure(void);

  void setPin(uint8_t pin);
  void addDelegate(middleware::interface::IDelegate * delegate);
  
  uint16_t getAbsoluteLoudness(void);
  int16_t getRelativeLoudness(void);

protected:
  uint16_t _absoluteLoudness;
  uint16_t _relativeLoudness;

  uint8_t _pin;
  Vector<middleware::interface::IDelegate *> _delegates;

  void invokeAllDelegates(void);
};

#endif // __LOUDNESSSENSOR_H__
