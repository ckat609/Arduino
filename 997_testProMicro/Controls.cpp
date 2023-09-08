#include "Arduino.h"
#include "Controls.h"

// *************** LED ***************
Led::Led() {}

Led::Led(int pin)
{
    _pin = pin;
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
    if (getState() == HIGH && millis() - _startTime > _duration && !_isTimeout)
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
    if (getState() == HIGH && millis() - _startTime > LONG && _isTimeout)
    {
        off();
    }
    _isTimeout = false;
}

// *************** PHOTORESISTOR ***************

PhotoResistor::PhotoResistor() {}

PhotoResistor::PhotoResistor(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
    _isTriggered = false;
    _sensitivity = MEDIUM;
}

PhotoResistor::PhotoResistor(int pin, int sensitivity)
{
    _pin = pin;
    pinMode(_pin, INPUT);
    _isTriggered = false;
    _sensitivity = sensitivity;
}

void PhotoResistor::init()
{
    _startValue = read();
}

int PhotoResistor::read()
{
    return analogRead(_pin);
}

int PhotoResistor::getStartValue()
{
    return _startValue;
}

bool PhotoResistor::triggered()
{
    int currentValue = read();
    bool wasTriggered = _isTriggered == false && _startValue - currentValue >= _sensitivity;

    if (wasTriggered)
    {
        _isTriggered = true;
    }

    return wasTriggered;
};

bool PhotoResistor::passed()
{
    int currentValue = read();
    bool hasPassed = _isTriggered == true && _startValue - currentValue < _sensitivity;

    if (hasPassed)
    {
        _isTriggered = false;
    }

    return hasPassed;
};

// *************** STEPPER ***************