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
    case (NONE):
        off();
        break;
    case (BLINK):
        if (millis() - _startTime > _duration)
        {
            off();
        }
        break;
    case (BLINKER):
        static long unsigned stBlinker = millis();
        if (millis() - stBlinker > _duration)
        {
            toggle();
            stBlinker = millis();
            if (read() == LOW)
            {
                _state = NONE;
            }
        }
        break;
    case (TIMEOUT):
        // static long unsigned _startTime = millis();
        if (read() == LOW && millis() - _startTime > _duration)
        {
            on();
        }
        // if (read() == HIGH && millis() - stTimeout > _duration)
        // {
        //     off();
        // }
        // if (millis() - _startTime > _duration)
        // {
        //     on();
        // }
        break;
    default:
        break;
    }
}

// *************** IR ***************

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
    case (NONE):

        if (dRead() == LOW)
        {
            _state = TRIGGERED;
            return _state;
        }
        break;
    case (TRIGGERED):
        if (dRead() == LOW)
        {
            _state = WAITING;
            return _state;
        }
        break;
    case (WAITING):
        if (dRead() == HIGH)
        {
            _state = PASSED;
            return _state;
        }
        break;
    case (PASSED):
        if (dRead() == HIGH)
        {
            _state = NONE;
            return _state;
        }
        break;
    }
    return _state;
}

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
    _direction = HIGH;
}
void Stepper::ccw()
{
    _direction = LOW;
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

void Stepper::zero()
{
    _state = ZERO;
    _delayTime = STEP_DELAY_SLOW;
    _direction = CCW;
}

void Stepper::home()
{
    _moving = true;
    _state = HOME;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::bag()
{
    _moving = true;
    _state = BAG;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::funnel()
{
    _moving = true;
    _state = FUNNEL;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::sucker()
{
    _moving = true;
    _state = SUCKER;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::drop()
{
    _moving = true;
    _state = DROP;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::move()
{
    if (_moving)
    {
        // step();
        switch (_state)
        {
        case (NONE):
            stop();
            break;
        case (ZERO):
            static int zeroStepCounter = 0;
            zeroStepCounter++;

            if (zeroStepCounter == ZERO_PULL_BACK_STEPS)
            {
                _state = NONE;
                zeroStepCounter = 0;
                POSITION_ZERO = 0;
            };
            break;
        case (HOME):
            if (_position > POSITION_HOME)
            {
                _position--;
                cw();
            }

            if (_position < POSITION_HOME)
            {
                _position++;
                ccw();
            }

            if (_position == POSITION_HOME)
            {
                _state = NONE;
            }
            else
            {
                step();
            }
            break;
        case (BAG):
            if (_position > POSITION_BAG)
            {
                _position--;
                cw();
            }

            if (_position < POSITION_BAG)
            {
                _position++;
                ccw();
            }

            if (_position == POSITION_BAG)
            {
                _state = NONE;
            }
            else
            {
                step();
            }
            break;
        case (FUNNEL):
            if (_position > POSITION_FUNNEL)
            {
                _position--;
                cw();
            }

            if (_position < POSITION_FUNNEL)
            {
                _position++;
                ccw();
            }

            if (_position == POSITION_FUNNEL)
            {
                _state = NONE;
            }
            else
            {
                step();
            }
            break;
        case (DROP):
            if (_position > POSITION_DROP)
            {
                _position--;
                cw();
            }

            if (_position < POSITION_DROP)
            {
                _position++;
                ccw();
            }

            if (_position == POSITION_DROP)
            {
                _state = NONE;
            }
            else
            {
                step();
            }
            break;
        default:
            break;
        }
    }
}