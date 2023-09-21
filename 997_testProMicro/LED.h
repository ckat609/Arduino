#ifndef LED_h
#define LED_h
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
#endif