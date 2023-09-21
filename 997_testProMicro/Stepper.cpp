#include "Arduino.h"
#include "Stepper.h"

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
    _direction = direction;
    _state = STEP;
    _delayTime = STEP_DELAY_SLOW;
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

int Stepper::getPosition()
{
    return _position;
}

void Stepper::reset()
{
    _state = RESET;
    _delayTime = STEP_DELAY_FAST;
    _direction = CW;
}

void Stepper::zero()
{
    _state = ZERO;
    _delayTime = STEP_DELAY_SLOW;
    _direction = CCW;
}

void Stepper::home()
{
    _state = HOME;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::bag()
{
    _state = BAG;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::funnel()
{
    _state = FUNNEL;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::sucker()
{
    _state = SUCKER;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::drop()
{
    _state = DROP;
    _delayTime = STEP_DELAY_FAST;
}

void Stepper::moveTo(int destination)
{
    if (_position > destination)
    {
        _position--;
        cw();
    }

    if (_position < destination)
    {
        _position++;
        ccw();
    }

    if (_position == destination)
    {
        _state = NONE;
    }
    else
    {
        step();
    }
}

void Stepper::move()
{
    {
        switch (_state)
        {
        case NONE:
            stop();
            break;
        case RESET:
            step();
            break;
        case STEP:
            if (_direction == CW && _position > POSITION_HOME)
            {
                _position--;
                step();
            }

            if (_direction == CCW && _position >= POSITION_HOME)
            {
                _position++;
                step();
            }
            Serial.println(_position);
            _state = NONE;
            break;
        case ZERO:
            static int zeroStepCounter = 0;
            zeroStepCounter++;

            if (zeroStepCounter == ZERO_PULL_BACK_STEPS)
            {
                _state = NONE;
                _position = 0;
                zeroStepCounter = 0;
                POSITION_HOME = 0;
            };
            break;
        case HOME:
            moveTo(POSITION_HOME);
            break;
        case BAG:
            moveTo(POSITION_BAG);
            break;
        case FUNNEL:
            moveTo(POSITION_FUNNEL);
            break;
        case DROP:
            moveTo(POSITION_DROP);
            break;
        default:
            break;
        }
    }
}