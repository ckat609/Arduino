#include "Arduino.h"
#include "LedControl.h"

Led::Led(int pin)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
}

void Led::on()
{
    digitalWrite(_pin, HIGH);
}

void Led::off()
{
    digitalWrite(_pin, LOW);
}

bool Led::getStatus()
{
    return digitalRead(_pin);
}

void Led::blink(int time)
{
    _start = millis();
    _duration = time;

    if (time > NONE)
    {
        on();
    }
    else
    {
        _type = "error";
        off();
    }
}

void Led::error(int time)
{
    _start = millis();
    _duration = time;
    digitalWrite(_pin, LOW);
}

void Led::check()
{
    if (getStatus() == HIGH && millis() - _start > _duration && _type != "error")
    {
        off();
    }

    if (getStatus() == LOW && millis() - _start > LONG && _type == "error")
    {
        on();
    }
}

void Led::clear()
{
    _type = "";
}