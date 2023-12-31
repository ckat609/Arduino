#ifndef Stepper_h
#define Stepper_h
#include "Arduino.h"

class Stepper
{
public:
    static const int STEPS_FULL_REV = 200;
    static const int STEP_DELAY_SLOW = 5000;
    static const int STEP_DELAY_MEDIUM = 2500;
    static const int STEP_DELAY_FAST = 1500;
    static const int STEP_DELAY_ULTRA = 500;
    static const int ZERO_PULL_BACK_STEPS = 25;
    static const bool CW = HIGH;
    static const bool CCW = LOW;

    Stepper();
    Stepper(int stepPin, int directionPin);
    Stepper(int stepPin, int directionPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin);
    Stepper(int stepPin, int directionPin, bool direction);
    Stepper(int stepPin, int directionPin, int delayTime, bool direction);
    void step();
    void step(bool direction);
    void stop();
    void cw();
    void ccw();
    int getPosition();
    int getState();
    void move();
    void moveTo(int destination);
    void reset();
    void zero();
    void home();
    void bag();
    void funnel();
    void sucker();
    void drop();
    void encoder(int destination);

private:
    int _stepPin;
    int _directionPin;
    int _enablePin;
    int _ms1Pin;
    int _ms2Pin;
    int _ms3Pin;
    bool _direction;
    int _delayTime;
    bool _moving;
    int _state;
    int _destination;
    int _position = 0;
    int POSITION_HOME = 0;
    int POSITION_BAG = 200;
    int POSITION_FUNNEL = 300;
    int POSITION_DROP = 500;

    enum _states
    {
        NONE,
        RESET,
        STEP,
        ZERO,
        HOME,
        BAG,
        FUNNEL,
        SUCKER,
        DROP,
        ENCODER
    };
};

#endif