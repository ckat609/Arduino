#include "LedControl.h"

const int stepPin = 3;
const int dirPin = 4;
const int greenPin = A0;
const int yellowPin = A1;
const int redPin = A3;
const int photoPin = A2;

const int shortBlink = 250;
const int mediumBlink = 500;
const int longBlink = 1000;

void countGummies();
void waitTime(void (*)());
void waitCandyState(void (*)());

bool greenLedState = false;
bool yellowLedState = false;
bool redLedState = false;

unsigned long photoStartTime = millis();
int photoStartVal;
int photoCurrentVal;
int photoSensitivity = 100;
int photoWait = 1500;
int photoTimeout = 2000;
bool photoState = false;

int motoSteps = 200;
int motoStepsDelay = 500;

int gummyCounter = 0;
int gummyCounerGlobal = 0;
int gummyMax = 3;

Led green(greenPin);
Led yellow(yellowPin);
Error red(redPin);

void setup()
{
    Serial.begin(115200);

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    photoStartVal = analogRead(photoPin);
}
void loop()
{
    green.off();
    yellow.off();
    // red.off();
    waitCandyState(photoStartVal, photoCurrentVal, photoSensitivity, photoState, countGummies);

    if (gummyCounter == gummyMax)
    {
        bool inLoop = true;
        green.on();
        digitalWrite(dirPin, HIGH);

        for (int x = 0; x < motoSteps; x++)
        {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(motoStepsDelay);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(motoStepsDelay);
        }
        gummyCounter = 0;
    }
}

void waitTime(long unsigned &startTime, int time, void (*callBackStart)())
{
    if (millis() - startTime >= time)
    {
        (*callBackStart)();
        startTime = millis();
    }
}

void waitCandyState(int startVal, int &currentVal, int delta, bool &state, void (*callBack)())
{
    currentVal = analogRead(photoPin);

    if (state == false && startVal - currentVal >= delta)
    {
        state = true;
    }

    if (state == true && startVal - currentVal < delta)
    {
        state = false;
        (*callBack)();
    }
}

void countGummies()
{

    Serial.print("DULCE: ");
    Serial.print(photoStartVal);
    Serial.print(" - ");
    Serial.print(photoCurrentVal);
    Serial.print(" = ");
    Serial.print(photoStartVal - photoCurrentVal);
    Serial.print(" ----> CURRENT: ");
    Serial.print(gummyCounter);
    Serial.print(" ----> TOTAL: ");
    Serial.println(gummyCounerGlobal);

    yellow.on();
    gummyCounter++;
    gummyCounerGlobal++;
}
