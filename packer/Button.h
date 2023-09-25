#ifndef Button_h
#define Button_h
#include "Arduino.h"

class Button
{
public:
    Button();
    Button(int pin);
    bool press();
    bool release();
    bool onPress();
    bool onRelease();
    bool read();

private:
    const int _duration = 25;
    int _pin;
    int _state;
    bool _wasDown;
    unsigned long _previousTime;

    enum _states
    {
        NONE,
        PRESSED,
        RELEASED,
        WAITING
    };
};

#endif