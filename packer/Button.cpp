#include "Arduino.h"
#include "Button.h"

Button::Button(){};

Button::Button(int pin)
{
    _pin = pin;
    _state = NONE;
    _previousTime = millis();
    _wasDown = false;

    pinMode(_pin, INPUT_PULLUP);
};

bool Button::press()
{
    if (_state == NONE && read() == LOW && millis() - _previousTime >= _duration)
    {
        _state = PRESSED;
        _previousTime = millis();
        return true;
    }
    if (_state == PRESSED && read() == LOW && millis() - _previousTime >= _duration)
    {
        _state = WAITING;
        _previousTime = millis();
        return false;
    }
    return false;
}

bool Button::release()
{
    if ((_state == WAITING || _state == PRESSED) && read() == HIGH && millis() - _previousTime >= _duration)
    {
        _state = RELEASED;
        _previousTime = millis();
        return true;
    }
    if (_state == RELEASED && read() == HIGH && millis() - _previousTime >= _duration)
    {
        _state = NONE;
        _previousTime = millis();
        return false;
    }

    return false;
}

bool Button::onPress()
{
    if (_state == NONE || _state == WAITING)
    {
        return press();
    }
    release();

    return false;
}

bool Button::onRelease()
{
    press();

    return release();
}

bool Button::read()
{
    return digitalRead(_pin);
}