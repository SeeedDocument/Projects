#ifndef __BIKETRACKER_H__
#define __BIKETRACKER_H__

#include "Arduino.h"
#include "ethernet.h"
#include "gnss.h"
#include "rgb_lcd.h"
//#include "Seeed_SHT35.h"
#include "string.h"
#include "WioLTEforArduino.h"

#include "IApplication.h"

#define HEART_BEAT_COUNT 20

namespace application {
  class BikeTracker;
}

class application::BikeTracker 
  : application::interface::IApplication {
public:
  void Setup(void);
  void Loop(void);
  
  void SetAPN(const char * apn);
  void SetPublishKey(const char * publishKey);
  void SetSubscribeKey(const char * subscribeKey);
  void SetChannel(const char * channel);
  void HeartBeat(void);
  
  static application::BikeTracker * GetInstance(void);
  
protected:
  WioLTE    _wio;
  Ethernet  _ethernet;
  GNSS      _gnss;
  rgb_lcd   _lcd;
//  SHT35     _sht35;
  
  const char *  _apn;
  const char *  _publishKey;
  const char *  _subscribeKey;
  const char *  _channel;
  
  BikeTracker(void);
  
  void PowerOn(void);
  void InitLCD(void);
  void OpenGNSS(void);
  void InitEthernet(void);

  double _longitude;
  double _latitude;
//  float _temperature;
  uint8_t _heartRate;
  uint8_t _heartBeatCount;
  unsigned long _heartBeat[HEART_BEAT_COUNT];

//  void MeasureTemperature(void);
  void PublishToPubNub(void);
  void PrintLCD(const char * line1, const char * line2);

  static const char * _server;
  static const int    _port;
  static application::BikeTracker _instance;
};

#endif // __BIKETRACKER_H__
