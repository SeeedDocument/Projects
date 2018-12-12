/*
 * DustMonitor.h
 * A Dust Monitor application class using Wio LTE Cat.1 & Grove - Laser PM2.5 Sensor (HM3301).
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
#ifndef __DUSTMONITOR_H__
#define __DUSTMONITOR_H__

#include "Arduino.h"
#include "ethernet.h"
#include "rgb_lcd.h"
#include "Seeed_HM330X.h"
#include "stdio.h"
#include "WioLTEforArduino.h"

#include "DustSensor.h"
#include "IApplication.h"

namespace application {
  class DustMonitor;
}

class application::DustMonitor
  : public application::interface::IApplication {
public:
  void setup(void);
  void loop(void);

  void setAPN(const char * apn);
  void setPublishKey(const char * publishKey);
  void setSubscribeKey(const char * subscribeKey);
  void setChannel(const char * channel);

  static application::DustMonitor * getInstance(void);

protected:
  WioLTE    _wio;
  rgb_lcd   _lcd;
  Ethernet  _ethernet;
  driver::DustSensor _sensor;

  const char *  _apn;
  const char *  _publishKey;
  const char *  _subscribeKey;
  const char *  _channel;

  static const char * _server;
  static const int    _port;
  static application::DustMonitor _instance;

  void powerOn(void);
  void initLCD(void);
  void initSensor(void);
  void initEthernet(void);
  
  void printLCD(void);
  void publishToPubNub(void);
  void printLCD(const char * line1, const char * line2);
};

#endif // __DUSTMONITOR_H__
