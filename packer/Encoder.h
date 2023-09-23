#ifndef Encoder_h
#define Encoder_h

class Encoder
{
public:
    Encoder();
    Encoder(int pinSW, int pinDT, int pinCLK);
    bool readSW();
    bool readCLK();
    bool readDT();
    bool isPressed();
    int check();
    void press();
    void toggle();

private:
    int _pinSW;
    int _pinCLK;
    int _pinDT;
    int _currentSW;
    int _previousSW;
    int _currentCLK;
    int _previousCLK;
    int _currentDT;
    int _previousDT;
    long _previousTime = millis();
    long _currentTime;
    int _state;
    int _value;

    enum states
    {
        NONE,
        PRESSED,
        TOGGLE
    };
};

#endif