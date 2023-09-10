#include "Arduino.h"
#include "Controls.h"

// *************** LED ***************
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

bool Led::getState()
{
    return _state;
}

void Led::setState(bool state)
{
    if (_previousController == _currentController)
    {
        _state = state;
    }
}

void Led::setState(bool state, char *controller)
{
    static char *ctrl;

    if (_state == false && state == true && ctrl != controller)
    {
        _state = state;
        ctrl = controller;
    }

    if (_state == true && state == false && ctrl == controller)
    {
        _state = state;
        ctrl = controller;
    }

    if (_state == state)
    {
        _state = state;
        ctrl = controller;
    }
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

void Led::blinker(int duration)
{
    static unsigned long startTime = millis();
    static char *controller;

    if (getState() == true && millis() - startTime > duration)
    {
        toggle();

        startTime = millis();
    }
    if (getState() == false)
    {
        off();
    }
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
    if (read() == HIGH && millis() - _startTime > _duration && !_isTimeout)
    {
        off();
    }
}

void Led::checkTimeout()
{
    if (read() == LOW && millis() - _startTime > LONG && _isTimeout)
    {
        on();
    }
}

void Led::clearTimeout()
{
    if (read() == HIGH && millis() - _startTime > LONG && _isTimeout)
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
    bool wasTriggered = _isTriggered == false && abs(_startValue - currentValue) >= _sensitivity;

    if (wasTriggered)
    {
        _isTriggered = true;
    }

    return wasTriggered;
};

bool PhotoResistor::passed()
{
    int currentValue = read();
    bool hasPassed = _isTriggered == true && abs(_startValue - currentValue) < _sensitivity;

    if (hasPassed)
    {
        _isTriggered = false;
    }

    return hasPassed;
};

// *************** STEPPER ***************

Stepper::Stepper(){

};

Stepper::Stepper(int stepPin, int directionPin)
{
    _stepPin = stepPin;
    _directionPin = directionPin;
    pinMode(_stepPin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    digitalWrite(_directionPin, CW);
}

Stepper::Stepper(int stepPin, int directionPin, bool direction)
{
    _stepPin = stepPin;
    _directionPin = directionPin;
    pinMode(_stepPin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    digitalWrite(_directionPin, direction);
}

void Stepper::step()
{
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(STEP_DELAY);
}

void Stepper::step(bool direction)
{
    digitalWrite(_directionPin, direction);
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(STEP_DELAY);
}

void Stepper::cw()
{
    digitalWrite(_directionPin, HIGH);
}
void Stepper::ccw()
{
    digitalWrite(_directionPin, LOW);
}

bool Stepper::getDirection()
{
    digitalRead(_directionPin);
}
