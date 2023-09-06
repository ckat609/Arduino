#include "Arduino.h"
#include "LedControl.h"


//time
#define NONE 0;
#define BLEEP 50;
#define SHORT 250;
#define MEDIUM 500;
#define LONG 1000;
#define ERROR 2000;

Led::Led(int pin)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
}

void Led::on()
{
      digitalWrite(_pin, HIGH);
}

void Led::off()
{
    digitalWrite(_pin, LOW);
}

bool Led::status()
{
    return digitalRead(_pin);
}

void Led::blink(char time){
        _start = millis();
        _duration = time;
        digitalWrite(_pin, HIGH);
}

void Led::blink(time time){
        _start = millis();
        _duration = time;
        digitalWrite(_pin, HIGH);
}

void Led::poop()
{
    if (_state == true && millis() - _start > _duration)
    {
        _state = false;
        digitalWrite(_pin, LOW);
    }
}

// Error::Error(int pin)
// {
//     pinMode(pin, OUTPUT);
//     _pin = pin;
//     _start = millis();
//     _state = false;
//     _duration = errorDuration;
// }

// void Error::on()
// {
//     if (millis() - _start > _duration)
//     {
//         digitalWrite(_pin, HIGH);
//     }
// }

// void Error::off(bool state)
// {
//     _state = false;
//     digitalWrite(_pin, LOW);
// }

// bool Error::getState()
// {
//     return _state;
// }
