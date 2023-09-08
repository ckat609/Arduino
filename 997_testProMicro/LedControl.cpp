#include "Arduino.h"
#include "LedControl.h"

// *************** LED ***************

Led::Led(int pin)
{
    _pin = pin;
    init();
}

void Led::init()
{
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

bool Led::getState()
{
    return digitalRead(_pin);
}

void Led::blink()
{
    _startTime = millis();
    _duration = SHORT;
    on();
}

void Led::blink(int duration)
{
    _startTime = millis();
    _duration = duration;
    on();
}

void Led::timeout()
{
    _startTime = millis();
    _duration = TIMEOUT;
    _isTimeout = true;
    off();
}

void Led::timeout(int waitDuration)
{
    _startTime = millis();
    _duration = waitDuration;
    _isTimeout = true;
    off();
}

void Led::checkBlink()
{
    if (getState() == HIGH && millis() - _startTime > _duration && _isTimeout)
    {
        off();
    }
}

void Led::checkTimeout()
{
    if (getState() == LOW && millis() - _startTime > LONG && _isTimeout)
    {
        on();
    }
}

void Led::clearTimeout()
{
    _isTimeout = false;
}

// *************** PHOTORESISTOR ***************

PhotoResistor::PhotoResistor(int pin)
{
    _pin = pin;
    init();
    _startTime = read();
}

void PhotoResistor::init()
{
    pinMode(_pin, INPUT);
}

int PhotoResistor::read()
{
    return analogRead(_pin);
}