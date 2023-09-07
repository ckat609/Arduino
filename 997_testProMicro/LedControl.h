#ifndef LedControl_h
#define LedControl_h
#include "Arduino.h"

class Led
{
public:
    // blink times
    static const int NONE = 0;
    static const int BLEEP = 50;
    static const int SHORT = 250;
    static const int MEDIUM = 500;
    static const int LONG = 1000;
    static const int ERROR = 2000;

    Led(int pin);
    void on();
    void off();
    bool getStatus();
    void blink(int time);
    void check();
    void error(int time);
    void clear();

private:
    long unsigned _start;
    int _pin;
    int _state;
    int _duration;
    char *_type;
};

#endif