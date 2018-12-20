/*
 * PIRSensor.h
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
#ifndef __PIRSENSOR_H__
#define __PIRSENSOR_H__

#include "IDelegate.h"
#include "ISensor.h"
#include "Vector.h"

namespace driver {
  class PIRSensor;
}

class driver::PIRSensor 
  : public driver::interface::ISensor {
public:
  PIRSensor();

  bool init(void);
  void measure(void);

  void setPin(uint8_t pin);
  void addDelegate(middleware::interface::IDelegate * delegate);
  
  bool isDetected(void);

protected:
  bool _detected;

  uint8_t _pin;
  Vector<middleware::interface::IDelegate *> _delegates;

  void invokeAllDelegates(void);
};

#endif // __PIRSENSOR_H__
