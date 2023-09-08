#ifndef LedControl_h
#define LedControl_h
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

    Led(int pin);
    void init();
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
    // blink times
    static const int SMALL = 50;
    static const int MEDIUM = 100;
    static const int LARGE = 250;
    static const int HUGE = 500;

    PhotoResistor(int pin);
    void init();
    int read();

private:
    long unsigned _startTime;
    int _pin;
    int _state;
    int _sensitivity;
    int _startValue;
    int _currentValue;
};

#endif