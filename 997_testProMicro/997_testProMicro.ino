#include "Controls.h"

const int stepPin = 3;
const int dirPin = 4;
const int ledGreenPin = 7;
const int ledYellowPin = 8;
const int ledRedPin = 9;
const int photoPin = 6;

// void waitTime(void (*)());

int gummyCounter = 0;
int gummyCounerGlobal = 0;
int gummyMax = 3;

Led ledGreen(ledGreenPin);
Led ledYellow(ledYellowPin);
Led ledRed(ledRedPin);

IR pr1(photoPin);

Stepper stepper1(stepPin, dirPin);

void setup()
{
    Serial.begin(115200);

    // pinMode(stepPin, OUTPUT);
    // pinMode(dirPin, OUTPUT);
    pinMode(10, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);

    pr1.init();
    // stepper1.home();
}
void loop()
{
    ledGreen.check();
    ledYellow.check();
    ledRed.check();
    stepper1.move();
    countCandy();

    if (digitalRead(16) == LOW)
    {
        stepper1.home();
        ledRed.blinker(100);
    }

    if (digitalRead(10) == LOW)
    {
        stepper1.bag();
        ledRed.blinker(100);
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

void countCandy()
{
    int checked = pr1.check();
    if (checked == pr1.TRIGGERED)
    {
        ledRed.timeout();
    }

    if (checked == pr1.PASSED)
    {

        ledYellow.blink(ledYellow.BLEEP);
        ledRed.clear();
        gummyCounter++;
        gummyCounerGlobal++;

        Serial.print(" ----> CURRENT: ");
        Serial.print(gummyCounter);
        Serial.print(" ----> TOTAL: ");
        Serial.println(gummyCounerGlobal);
    }

    checkMaxCandy();
}

void checkMaxCandy()
{
    int maxSteps = 200;
    static int currStep = 0;

    if (gummyCounter == gummyMax)
    {
        ledGreen.blink(ledGreen.SHORT);
        stepper1.cw();

        if (currStep < maxSteps)
        {
            stepper1.step();
        }
        else
        {
            currStep = 0;
        }
        gummyCounter = 0;
    }
}
