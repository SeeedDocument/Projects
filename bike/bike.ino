#include "BikeTracker.h"
#include "IApplication.h"

using namespace application;

BikeTracker * tracker = BikeTracker::GetInstance();

void heartBeat(void) {
  tracker->HeartBeat();
}

void setup(void) {
  tracker->SetAPN("<your_apn>");
  tracker->SetPublishKey("<your_publish_key>");
  tracker->SetSubscribeKey("<your_subscribe_key>");
  tracker->SetChannel("<your_channel>");
  
  tracker->Setup();
  attachInterrupt(WIOLTE_D20, heartBeat, RISING);
}

void loop(void) {
  tracker->Loop();
}
