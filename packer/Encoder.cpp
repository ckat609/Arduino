#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder() {}

Encoder::Encoder(int pinDT, int pinCLK)
{
    _pinDT = pinDT;
    _pinCLK = pinCLK;

    pinMode(pinDT, INPUT);
    pinMode(pinCLK, INPUT);

    _previousDT = digitalRead(_pinDT);
    _previousCLK = digitalRead(_pinCLK);
}

bool Encoder::readDT()
{
    return digitalRead(_pinDT);
}

bool Encoder::readCLK()
{
    return digitalRead(_pinCLK);
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