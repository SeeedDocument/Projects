#include "DrinkingData.h"

DrinkingData::DrinkingData(uint8_t ultrasonicPin)
    : _ultrasonic(Ultrasonic(ultrasonicPin)), _rtc(RtcDS1307<TwoWire>(Wire)), 
    _goal(0), _progress(0), _continuously(0), _alertInterval(0), 
    _distanceSum(0L), _distanceCount(0), _lastDistance(0), 
    _lastDrink(0)
{
    // do nothing
}

void DrinkingData::updateProgress()
{
    _distanceSum += _ultrasonic.MeasureInCentimeters();
    if (++_distanceCount == 10)
    {
        uint16_t currentDistance = _distanceSum / _distanceCount;
        if (_lastDistance != 0 && _lastDistance < currentDistance)
        {
            _progress += (currentDistance - _lastDistance) * 40;
            _lastDrink = millis();
        }

        _lastDistance = currentDistance;
        _distanceSum = 0;
        _distanceCount = 0;
    }
}

void DrinkingData::updateContinuously()
{
    RtcDateTime now = _rtc.GetDateTime();

    if (now.Hour() == 0 && now.Minute() && now.Second())
    {
        if (_progress >= _goal)
        {
            ++_continuously;
        }

        _progress = 0;
    }
}

bool DrinkingData::getAlert()
{
    return millis() - _lastDrink > _alertInterval * 60 * 1000;
}

uint16_t DrinkingData::getGoal()
{
    return _goal;
}

uint16_t DrinkingData::getProgress()
{
    return _progress;
}

uint16_t DrinkingData::getContinuously()
{
    return _continuously;
}

void DrinkingData::setGoal(uint16_t ml)
{
    _goal = ml;
}

void DrinkingData::setAlertInterval(uint8_t minute)
{
    _alertInterval = minute;
}
