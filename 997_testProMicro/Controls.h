#ifndef Controls_h
#define Controls_h
#include "Arduino.h"

class Led
{
public:
    // blink times
    static const int BLEEP = 50;
    static const int SHORT = 250;
    static const int MEDIUM = 500;
    static const int LONG = 1000;
    static const int OUT = 1000;

    Led();
    Led(int pin);
    void on();
    void off();
    bool read();
    void blink();
    void blink(int duration);
    void blinker(int duration);
    void check();
    void toggle();
    void timeout();
    void timeout(int waitDuration);
    void clear();

private:
    int _pin;
    long unsigned _startTime;
    int _duration;
    int _state;
    enum _states
    {
        NONE,
        BLINK,
        BLINKER,
        TIMEOUT,
    };
};

class IR
{
public:
    // sensitivities
    static const int SMALL = 50;
    static const int MEDIUM = 100;
    static const int LARGE = 250;
    static const int HUGE = 500;
    enum _states
    {
        NONE,
        TRIGGERED,
        WAITING,
        PASSED
    };

    IR();
    IR(int pin);
    IR(int pin, int sensitivity);
    void init();
    int aRead();
    int dRead();
    int check();

private:
    int _pin;
    int _sensitivity;
    int _startValue;
    int _currentValue;
    int _state;
};

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
    void setDirection(bool direction);
    bool getDirection();
    void setDelayTime(int delayTime);
    int getDelayTime();
    void setState(int state);
    int getState();
    void move();
    void zero();
    void home();
    void bag();
    void funnel();
    void sucker();
    void drop();

private:
    int _stepPin;
    int _directionPin;
    bool _direction;
    int _delayTime;
    bool _moving;
    int _state;
    int _position = 0;
    int POSITION_ZERO = 0;
    int POSITION_HOME = 0;
    int POSITION_BAG = 200;
    int POSITION_FUNNEL = 300;
    int POSITION_DROP = 500;

    enum _states
    {
        NONE,
        ZERO,
        HOME,
        BAG,
        FUNNEL,
        SUCKER,
        DROP
    };
};

#endif