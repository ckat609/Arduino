#include "Arduino.h"
#include "IR.h"

IR::IR() {}

IR::IR(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
    _state = NONE;
    _sensitivity = MEDIUM;
}

IR::IR(int pin, int sensitivity)
{
    _pin = pin;
    pinMode(_pin, INPUT);
    _state = NONE;
    _sensitivity = sensitivity;
}

void IR::init()
{
    _startValue = dRead();
}

int IR::aRead()
{
    return analogRead(_pin);
}

int IR::dRead()
{
    return digitalRead(_pin);
}

int IR::check()
{
    switch (_state)
    {
    case NONE:

        if (dRead() == LOW)
        {
            _state = TRIGGERED;
            return _state;
        }
        break;
    case TRIGGERED:
        if (dRead() == LOW)
        {
            _state = WAITING;
            return _state;
        }
        break;
    case WAITING:
        if (dRead() == HIGH)
        {
            _state = PASSED;
            return _state;
        }
        break;
    case PASSED:
        if (dRead() == HIGH)
        {
            _state = NONE;
            return _state;
        }
        break;
    }
    return _state;
}