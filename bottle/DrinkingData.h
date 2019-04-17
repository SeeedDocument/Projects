#ifndef __DRINKINGDATA_H__
#define __DRINKINGDATA_H__

#include "Arduino.h"
#include "Wire.h"

#include "RtcDS1307.h"
#include "Ultrasonic.h"

class DrinkingData
{
public:
    DrinkingData(uint8_t ultrasonicPin);

    void updateProgress();
    void updateContinuously();

    bool getAlert();
    uint16_t getGoal();
    uint16_t getProgress();
    uint16_t getContinuously();

    void setGoal(uint16_t ml);
    void setAlertInterval(uint8_t minute);
    
protected:
    Ultrasonic _ultrasonic;
    RtcDS1307<TwoWire> _rtc;

    uint16_t _goal;
    uint16_t _progress;
    uint16_t _continuously;
    uint8_t _alertInterval;

    long _distanceSum;
    uint8_t _distanceCount;
    uint16_t _lastDistance;

    long _lastDrink;
};

#endif // __DRINKINGDATA_H__
