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
    static const int ZERO_PULL_BACK_STEPS = 5;
    static const bool CW = HIGH;
    static const bool CCW = LOW;

    Stepper();
    Stepper(int stepPin, int directionPin);
    Stepper(int stepPin, int directionPin, bool direction);
    Stepper(int stepPin, int directionPin, int delayTime, bool direction);
    void step();
    void step(bool direction);
    void stop();
    void cw();
    void ccw();
    int getPosition();
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