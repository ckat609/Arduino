#ifndef Encoder_h
#define Encoder_h

class Encoder
{
public:
    Encoder();
    Encoder(int pinDT, int pinCLK);
    bool readCLK();
    bool readDT();
    int check();

private:
    int _pinSW;
    int _pinCLK;
    int _pinDT;
    int _currentCLK;
    int _previousCLK;
    int _currentDT;
    int _previousDT;
    long _previousTime = millis();
    long _currentTime;
    int _state;

    enum states
    {
        NONE,
        PRESSED,
        TOGGLE
    };
};

#endif