#ifndef IR_h
#define IR_h
#include "Arduino.h"

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

#endif