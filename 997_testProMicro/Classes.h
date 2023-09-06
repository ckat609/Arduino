#ifndef Classes_h
#define Classes_h
#include "Arduino.h"

class Led
{
public:
    Led(int pin);
    Led(int pin, int duration);
    void on();
    void off();

private:
    int _pin;
    int _state;
    long unsigned _start;
    int _duration;
};

class Error
{
public:
    Error(int pin);
    void on();
    void off(bool state);
    bool getState();

private:
    int _pin;
    int _state;
    long unsigned _start;
    int _duration;
};

#endif