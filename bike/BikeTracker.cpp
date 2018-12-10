#include "BikeTracker.h"

#define __CMD_LEN 512

using namespace application;
using namespace application::interface;

const char *  BikeTracker::_server  = "ps.pndsn.com";
const int     BikeTracker::_port    = 80;

BikeTracker BikeTracker::_instance;

void BikeTracker::Setup(void) {
  delay(200);

  // power on grove supply
  _wio.Init();
  _wio.PowerSupplyGrove(true);
  delay(500);

  InitLCD();
  
  PowerOn();
  InitEthernet();
  OpenGNSS();

  delay(1000);
}

void BikeTracker::Loop(void) {
  static uint8_t i = 0;
  static const char * arr[] = {
    "Locating", 
    "Locating.",
    "Locating..",
    "Locating..."
  };
  
  char line1[16] = {0};
  char line2[16] = {0};
  
  if (_gnss.getCoordinate()) {
    _longitude = _gnss.longitude;
    _latitude = _gnss.latitude;

    PublishToPubNub();
    sprintf(line1, "%7f, %7f", _longitude, _latitude);
  } else {
    sprintf(line1, "%s", arr[i = (i + 1) % 4]);
  }
  
  sprintf(line2, "Heart Rate: %d", _heartRate);
  
//  MeasureTemperature();
//  sprintf(line2, "Temp: %f", _temperature);

  PrintLCD(line1, line2);
}

void BikeTracker::SetAPN(const char * apn) {
  _apn = apn;
}

void BikeTracker::SetPublishKey(const char * publishKey) {
  _publishKey = publishKey;
}

void BikeTracker::SetSubscribeKey(const char * subscribeKey) {
  _subscribeKey = subscribeKey;
}

void BikeTracker::SetChannel(const char * channel) {
  _channel = channel;
}

void BikeTracker::HeartBeat(void) {
  _heartBeat[_heartBeatCount++] = millis();
  
  if (_heartBeatCount == HEART_BEAT_COUNT) {
    _heartRate = 1200000/(_heartBeat[HEART_BEAT_COUNT - 1]-_heartBeat[0]);
    _heartBeatCount = 0;
  }
}

BikeTracker * BikeTracker::GetInstance(void) {
  return &_instance;
}

BikeTracker::BikeTracker(void) 
  : _ethernet(Ethernet()), _gnss(GNSS()) { }

//BikeTracker::BikeTracker(void) 
//  : _ethernet(Ethernet()), _gnss(GNSS()), _sht35(SHT35(21)) { }

void BikeTracker::PowerOn(void) {
  _ethernet.Power_On();
  _gnss.Power_On();
  
  while (!_ethernet.Check_If_Power_On() || !_gnss.Check_If_Power_On()) {
    PrintLCD("Waiting modules to alive...", "");
    delay(1000);
  }

  PrintLCD("Waiting modules to alive...", "Modules alived.");
}

void BikeTracker::InitLCD(void) {
  _lcd.begin(16, 2);
  _lcd.setRGB(255, 255, 255);

  _lcd.print("Loading...");
}

void BikeTracker::InitEthernet(void) {
  while (!_ethernet.init()) {
    PrintLCD("Accessing network...", "");
    delay(1000);
  }

  _ethernet.join(_apn);
  PrintLCD("Accessing network...", "Accessed network.");
}

void BikeTracker::OpenGNSS(void) {
  PrintLCD("Opening GNSS...", "");
  
  if (!_gnss.open_GNSS()) {
    PrintLCD("Opening GNSS...", "Open GNSS FAILED.");
    return;
  }
  
  PrintLCD("Opening GNSS...", "GNSS Opened.");
  delay(2000);
}

//void BikeTracker::MeasureTemperature(void) {
//  float temperature, humidity;
//  if (_sht35.read_meas_data_single_shot(HIGH_REP_WITH_STRCH,&temperature,&humidity) == NO_ERROR) {
//    _temperature = temperature;
//  }
//}

void BikeTracker::PublishToPubNub(void) {
  char cmd[__CMD_LEN] = {0};
  sprintf(cmd, "GET /publish/%s/%s/0/%s/0/%%5b%%7b%%22latlng%%22%%3a%%5b%f%%2c%f%%5d%%2c%%22data%%22%%3a%d%%7d%%5d?store=0 HTTP/1.0\n\r\n\r", 
      _publishKey, _subscribeKey, _channel, _latitude, _longitude, _heartRate);
//  sprintf(cmd, "GET /publish/%s/%s/0/%s/0/%%5b%%7b%%22latlng%%22%%3a%%5b%f%%2c%f%%5d%%2c%%22data%%22%%3a%f%%7d%%5d?store=0 HTTP/1.0\n\r\n\r", 
//      _publishKey, _subscribeKey, _channel, _latitude, _longitude, _temperature);
  
  InitEthernet();
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

void BikeTracker::PrintLCD(const char * line1, const char * line2) {
  _lcd.clear();
  
  _lcd.setCursor(0, 0);
  _lcd.print(line1);

  _lcd.setCursor(0, 1);
  _lcd.print(line2);
}
