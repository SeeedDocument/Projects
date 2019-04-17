#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Arduino.h"
#include "Wire.h"

#include "RtcDS1307.h"
#include "SeeedGrayOLED.h"

class Display
{
public:
    Display();

    void init();

    void showDateTime();
    void showProgress(uint16_t progress, uint16_t goal);
    void showContinuously(uint16_t days);

    void showAlert(bool alert);

protected:
    RtcDS1307<TwoWire> _rtc;

    bool _showAlert;
    long _lastAlert;
};

#endif // __DISPLAY_H__
