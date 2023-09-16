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

void Led::setState(bool state, char *controller)
{
    static char *ctrl;
    if (_state == false && state == true && _controller != controller)
    {
        _state = state;
        _controller = controller;
    }

    if (_state == true && state == false && _controller == controller)
    {
        _state = state;
        _controller = controller;
    }

    if (_state == state)
    {
        _state = state;
        _controller = controller;
    }
    _previousController = _controller;
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

void Led::checkBlink()
{
    if (read() == HIGH && millis() - _startTime > _duration && !_isTimeout)
    {
        off();
    }
}

void Led::timeout(int waitDuration)
{
    _startTime = millis();
    _duration = waitDuration;
    _isTimeout = true;
    off();
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

// *************** IR ***************

IR::IR() {}

IR::IR(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
    _isTriggered = false;
    _sensitivity = MEDIUM;
}

IR::IR(int pin, int sensitivity)
{
    _pin = pin;
    pinMode(_pin, INPUT);
    _isTriggered = false;
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

int IR::getStartValue()
{
    return _startValue;
}

bool IR::triggered()
{
    int currentValue = dRead();
    bool wasTriggered = _isTriggered == false && dRead() == LOW;

    if (wasTriggered)
    {
        _isTriggered = true;
    }

    return wasTriggered;
};

bool IR::passed()
{
    int currentValue = dRead();
    bool hasPassed = _isTriggered == true && dRead() == HIGH;

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
    _delayTime = STEP_DELAY_MEDIUM;
    pinMode(_stepPin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    digitalWrite(_directionPin, direction);
}

Stepper::Stepper(int stepPin, int directionPin, int delayTime, bool direction)
{
    _stepPin = stepPin;
    _directionPin = directionPin;
    _delayTime = delayTime;
    pinMode(_stepPin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    digitalWrite(_directionPin, direction);
}

void Stepper::step()
{
    digitalWrite(_directionPin, _direction);
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(_delayTime);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(_delayTime);
}

void Stepper::step(bool direction)
{
    digitalWrite(_directionPin, direction);
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(_delayTime);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(_delayTime);
}

void Stepper::stop()
{
    _moving = false;
}

void Stepper::cw()
{
    digitalWrite(_directionPin, HIGH);
}
void Stepper::ccw()
{
    digitalWrite(_directionPin, LOW);
}

void Stepper::setDirection(bool direction)
{
    _direction = direction;
}

bool Stepper::getDirection()
{
    return _direction;
}

void Stepper::setDelayTime(int delayTime)
{
    _delayTime = delayTime;
}

int Stepper::getDelayTime()
{
    return _delayTime;
}

void Stepper::setState(int state)
{
    _state = state;
}

int Stepper::getState()
{
    return _state;
}

void Stepper::home()
{
    _moving = true;
    _state = HOME;
    _delayTime = STEP_DELAY_FAST;
    _direction = CW;
}

void Stepper::zero()
{
    _state = ZERO;
    _delayTime = STEP_DELAY_SLOW;
    _direction = CCW;
}

void Stepper::move()
{
    static int zeroStepCounter = 0;

    if (_moving)
    {
        step();
        switch (_state)
        {
        case (ZERO):
            zeroStepCounter++;
            if (zeroStepCounter == ZERO_PULL_BACK_STEPS)
            {
                _state = NONE;
                zeroStepCounter = 0;
            };
            break;
        case (HOME):
            break;
        case (NONE):
            stop();
            break;
        default:
            break;
        }
    }

    // if (sstate != true)
    // {
    //     step();
    //     if (_zero == true)
    //     {
    //         Serial.print("ZERO: ");
    //         Serial.println(zeroStepCounter);
    //         zeroStepCounter++;
    //         if (zeroStepCounter == ZERO_PULL_BACK_STEPS)
    //         {
    //             _zero = false;
    //             _state = false;
    //             zeroStepCounter = 0;
    //         };
    //     }
    // }
}