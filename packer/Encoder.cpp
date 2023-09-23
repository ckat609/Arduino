#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder() {}

Encoder::Encoder(int pinSW, int pinDT, int pinCLK)
{
    _pinSW = pinSW;
    _pinDT = pinDT;
    _pinCLK = pinCLK;

    pinMode(pinSW, INPUT_PULLUP);
    pinMode(pinDT, INPUT);
    pinMode(pinCLK, INPUT);

    _previousSW = digitalRead(_pinSW);
    _previousDT = digitalRead(_pinDT);
    _previousCLK = digitalRead(_pinCLK);
}

bool Encoder::readSW()
{
    return digitalRead(_pinSW);
}

bool Encoder::readDT()
{
    return digitalRead(_pinDT);
}

bool Encoder::readCLK()
{
    return digitalRead(_pinCLK);
}

void Encoder::press()
{
    int duration = 250;
    _currentTime = millis();
    _currentSW = readSW();

    if (_currentSW == LOW && _previousSW == HIGH && _currentTime - _previousTime >= duration)
    {
        _state = PRESSED;
        _previousTime = _currentTime;
    }
    _previousSW = _currentSW;
}

bool Encoder::isPressed()
{
    switch (_state)
    {
    case NONE:
        press();
        return false;
        break;
    case PRESSED:
        _state = NONE;
        return true;

        break;
    }
}

int Encoder::check()
{
    static int count = 0;

    _currentCLK = digitalRead(_pinCLK);
    _currentDT = digitalRead(_pinDT);

    if (_currentCLK != _previousCLK)
    {
        if (_currentCLK == _currentDT)
        {
            if (count > 0)
            {
                count--;
            }
        }
        else
        {
            count++;
        }
    }
    _previousCLK = _currentCLK;
    return count;
}