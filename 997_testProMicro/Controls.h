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
    static const int TIMEOUT = 5000;

    Led();
    Led(int pin);
    void on();
    void off();
    bool getState();
    void blink();
    void blink(int duration);
    void checkBlink();
    void timeout();
    void timeout(int waitDuration);
    void checkTimeout();
    void clearTimeout();

private:
    long unsigned _startTime;
    int _pin;
    int _duration;
    bool _isTimeout;
};

class PhotoResistor
{
public:
    // sensitivities
    static const int SMALL = 50;
    static const int MEDIUM = 100;
    static const int LARGE = 250;
    static const int HUGE = 500;

    PhotoResistor();
    PhotoResistor(int pin);
    PhotoResistor(int pin, int sensitivity);
    void init();
    int read();
    int getStartValue();
    bool triggered();
    bool passed();

private:
    int _pin;
    int _sensitivity;
    int _startValue;
    int _currentValue;
    bool _isTriggered;
    Led _passedLed;
    Led _timeoutLed;
};

class Stepper
{
public:
    static const int STEPS_FULL_REV = 200;
    static const int motoStepsDelay = 500;
    static const bool CW = HIGH;
    static const bool CCW = LOW;

    Stepper();
    Stepper(int stepPin, bool directionPin);

private:
};

#endif