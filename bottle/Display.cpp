#include "Display.h"

#define oled            SeeedGrayOled
#define LINE_LENGTH     ((uint8_t)16)
#define ALERT_INTERVAL  ((uint8_t)500)

Display::Display() 
    : _rtc(RtcDS1307<TwoWire>(Wire)), 
    _showAlert(false), _lastAlert(0L)
{
    // do nothing
}

void Display::init()
{
    oled.init(SH1107G);
    oled.clearDisplay();
    oled.setNormalDisplay();
    oled.setVerticalMode();
}

void Display::showDateTime()
{
    RtcDateTime now = _rtc.GetDateTime();
    char buffer[LINE_LENGTH + 1] = {0};

    oled.setTextXY(1, 0);
    sprintf(buffer, "   %04u/%02u/%02u   ", now.Year(), now.Month(), now.Day());
    oled.putString(buffer);

    oled.setTextXY(2, 0);
    sprintf(buffer, "    %02u:%02u:%02u    ", now.Hour(), now.Minute(), now.Second());
    oled.putString(buffer);
}

void Display::showProgress(uint16_t progress, uint16_t goal)
{
    char buffer[LINE_LENGTH + 1] = {0};

    oled.setTextXY(5, 0);
    oled.putString("  Today's Goal  ");

    oled.setTextXY(7, 0);
    sprintf(buffer, "  %04u/%04u ml  ", progress, goal);
    oled.putString(buffer);
}

void Display::showContinuously(uint16_t days)
{
    char buffer[LINE_LENGTH + 1] = {0};

    oled.setTextXY(10, 0);
    oled.putString("  Continuously  ");

    oled.setTextXY(12, 0);
    sprintf(buffer, "    %04u day    ", days);
    oled.putString(buffer);
}

void Display::showAlert(bool alert)
{
    char buffer[LINE_LENGTH + 1] = {0};

    oled.setTextXY(15, 0);

    if (!alert)
    {
        sprintf(buffer, "%16s", " ");
        oled.putString(buffer);

        return;
    }

    if (_lastAlert == 0 || millis() - _lastAlert >= ALERT_INTERVAL)
    {
        sprintf(buffer, "%16s", _showAlert ? " " : "!!DRINK ALERT!!!");
        oled.putString(buffer);

        _lastAlert = millis();
        _showAlert = !_showAlert;
    }
}
