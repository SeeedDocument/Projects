/*
 * DustMonitor.cpp
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
#include "DustMonitor.h"

#define __CMD_LEN 512

using namespace application;
using namespace application::interface;

const char *  DustMonitor::_server  = "ps.pndsn.com";
const int     DustMonitor::_port    = 80;
DustMonitor   DustMonitor::_instance;

void DustMonitor::setup(void) {
  initLCD();

  powerOn();
  initSensor();
  initEthernet();
}

void DustMonitor::loop(void) {
  _sensor.measure();

  publishToPubNub();
  printLCD();
}

void DustMonitor::setAPN(const char * apn) {
  _apn = apn;
}

void DustMonitor::setPublishKey(const char * publishKey) {
  _publishKey = publishKey;
}

void DustMonitor::setSubscribeKey(const char * subscribeKey) {
  _subscribeKey = subscribeKey;
}

void DustMonitor::setChannel(const char * channel) {
  _channel = channel;
}

DustMonitor * DustMonitor::getInstance(void) {
  return &_instance;
}

void DustMonitor::powerOn(void) {
  _ethernet.Power_On();
  
  while (!_ethernet.Check_If_Power_On()) {
    printLCD("Waiting modules to alive...", "");
    delay(1000);
  }

  printLCD("Waiting modules to alive...", "Modules alived.");
}

void DustMonitor::initLCD(void) {
  delay(200);

  _wio.Init();
  _wio.PowerSupplyGrove(true);
  delay(500);
  
  _lcd.begin(16, 2);
  _lcd.setRGB(255, 255, 255);

  _lcd.print("Loading...");
}

void DustMonitor::initSensor(void) {
  _sensor.init();
}

void DustMonitor::initEthernet(void) {
  while (!_ethernet.init()) {
    printLCD("Accessing network...", "");
    delay(1000);
  }

  _ethernet.join(_apn);
  printLCD("Accessing network...", "Accessed network.");
}

void DustMonitor::printLCD(void) {
  char buffer[16] = {0};
  
  sprintf(buffer, "%11dug/m3", _sensor.getPM1());
  printLCD("PM1.0", buffer);
  delay(3000);

  sprintf(buffer, "%11dug/m3", _sensor.getPM25());
  printLCD("PM2.5", buffer);
  delay(3000);

  sprintf(buffer, "%11dug/m3", _sensor.getPM10());
  printLCD("PM10", buffer);
  delay(3000);
}

void DustMonitor::publishToPubNub(void) {
  char cmd[__CMD_LEN] = {0};
  sprintf(cmd, "GET /publish/%s/%s/0/%s/0/%%7b%%22pm1%%22%%3a%d%%2c%%22pm25%%22%%3a%d%%2c%%22pm10%%22%%3a%d%%7d?store=0 HTTP/1.0\n\r\n\r", 
      _publishKey, _subscribeKey, _channel, _sensor.getPM1(), _sensor.getPM25(), _sensor.getPM10());
  
  initEthernet();
  if (_ethernet.connect(_server, _port, TCP)) {
    _ethernet.write(cmd);
    SerialUSB.println(cmd);
    
    while(MODULE_PORT.available()) {
      serialDebug.write(MODULE_PORT.read());
    }
    
    MODULE_PORT.flush();
    _ethernet.close(1);
  } else {
    SerialUSB.println("Connect FAILED.");
  }
}

void DustMonitor::printLCD(const char * line1, const char * line2) {
  _lcd.clear();
  
  _lcd.setCursor(0, 0);
  _lcd.print(line1);

  _lcd.setCursor(0, 1);
  _lcd.print(line2);
}
