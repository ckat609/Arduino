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

Stepper::Stepper(int stepPin, int directionPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin)
{
    _stepPin = stepPin;
    _directionPin = directionPin;
    _delayTime = STEP_DELAY_MEDIUM;
    pinMode(_stepPin, OUTPUT);
    pinMode(_directionPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    pinMode(_ms1Pin, OUTPUT);
    pinMode(_ms2Pin, OUTPUT);
    pinMode(_ms3Pin, OUTPUT);
    digitalWrite(_directionPin, CW);
    digitalWrite(_enablePin, LOW);
    digitalWrite(_ms1Pin, LOW);
    digitalWrite(_ms2Pin, LOW);
    digitalWrite(_ms3Pin, LOW);
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

int Stepper::getState()
{
    return _state;
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

void Stepper::encoder(int destination)
{
    _state = ENCODER;
    _delayTime = STEP_DELAY_FAST;
    _destination = destination;
}

void Stepper::moveTo(int destination)
{
    _destination = destination;

    if (_position > _destination)
    {
        _position--;
        cw();
    }

    if (_position < _destination)
    {
        _position++;
        ccw();
    }

    if (_position == _destination)
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
            _state = NONE;
            break;
        case ZERO:
            static int zeroStepCounter = 0;

            zeroStepCounter++;
            step();

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
        case ENCODER:
            moveTo(_destination);
            break;
        default:
            break;
        }
    }
}