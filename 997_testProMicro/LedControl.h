#ifndef LedControl_h
#define LedControl_h
#include "Arduino.h"

class Led
{
public:
    Led(int pin);
    void on();
    void off();
    bool status();
    void blink(char time[]);
    void blink(time time);
    void poop();

private:
    long unsigned _start;
    int _pin;
    int _state;
    int _duration;
    char _type[] ;
};

#endif