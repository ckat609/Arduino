#include "Arduino.h"
#include "Classes.h"

int bleep = 50;
int shortDuration = 250;
int mediumDuration = 500;
int longDuration = 1000;
int errorDuration = 2000;

Led::Led(int pin)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _start = false;
    _duration = shortDuration;
}

Led::Led(int pin, int duration)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _start = false;
    _duration = duration;
}

void Led::on()
{
    if (_state == false)
    {
        _start = millis();
        _state = true;
        digitalWrite(_pin, HIGH);
    }
}

void Led::off()
{
    if (_state == true && millis() - _start > _duration)
    {
        _state = false;
        digitalWrite(_pin, LOW);
    }
}

Error::Error(int pin)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _start = millis();
    _state = false;
    _duration = errorDuration;
}

void Error::on()
{
    if (millis() - _start > _duration)
    {
        digitalWrite(_pin, HIGH);
    }
}

void Error::off(bool state)
{
    _state = false;
    digitalWrite(_pin, LOW);
}

bool Error::getState()
{
    return _state;
}
