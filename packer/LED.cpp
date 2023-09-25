#include "Arduino.h"
#include "LED.h"

Led::Led() {}

Led::Led(int pin)
{
    _pin = pin;
    _state = false;
    pinMode(_pin, OUTPUT);
}

void Led::on()
{
    digitalWrite(_pin, HIGH);
}

void Led::off()
{
    digitalWrite(_pin, LOW);
}

bool Led::read()
{
    return digitalRead(_pin);
}

void Led::blink()
{
    _state = BLINK;
    _startTime = millis();
    _duration = SHORT;
    on();
}

void Led::blink(int duration)
{
    _state = BLINK;
    _startTime = millis();
    _duration = duration;
    on();
}

void Led::blinker(int duration)
{
    _state = BLINKER;
    _startTime = millis();
    _duration = duration;
}

void Led::toggle()
{
    if (read() == HIGH)
    {
        off();
    }
    else
    {
        on();
    }
}

void Led::timeout()
{
    _state = TIMEOUT;
    _startTime = millis();
    _duration = 1000;
}

void Led::timeout(int waitDuration)
{
    _state = TIMEOUT;
    _startTime = millis();
    _duration = waitDuration;
}

void Led::clear()
{
    _state = NONE;
}

void Led::check()
{

    switch (_state)
    {
    case NONE:
        off();
        break;
    case (BLINK):
        if (millis() - _startTime > _duration)
        {
            _state = NONE;
        }
        break;
    case BLINKER:
        static long unsigned stBlinker = millis();
        if (millis() - stBlinker > _duration)
        {
            toggle();
            stBlinker = millis();
                }
        break;
    case TIMEOUT:
        if (read() == LOW && millis() - _startTime > _duration)
        {
            on();
        }
        break;
    default:
        break;
    }
}
