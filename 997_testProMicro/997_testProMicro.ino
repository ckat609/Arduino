#include "LED.h"
#include "IR.h"
#include "Stepper.h"

const int stepPin = 3;
const int dirPin = 4;
const int ledGreenPin = 7;
const int ledYellowPin = 8;
const int ledRedPin = 9;
const int photoPin = 6;

// void waitTime(void (*)());

Led ledGreen(ledGreenPin);
Led ledYellow(ledYellowPin);
Led ledRed(ledRedPin);

IR pr1(photoPin);

Stepper stepper1(stepPin, dirPin);

void setup()
{
    Serial.begin(115200);

    pinMode(10, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);

    pr1.init();
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
        stepper1.drop();
        ledRed.blinker(100);
    }

    if (digitalRead(10) == LOW)
    {
        stepper1.home();
        ledRed.blinker(100);
    }
}

void countCandy()
{
    static int gummyCounter = 0;
    static int gummyCounerGlobal = 0;
    static int gummyMax = 3;

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

        Serial.print("CURRENT: ");
        Serial.print(gummyCounter);
        Serial.print(" ----> TOTAL: ");
        Serial.println(gummyCounerGlobal);
    }

    if (gummyCounter == gummyMax)
    {
        ledGreen.blink(ledGreen.SHORT);
        stepper1.funnel();
        gummyCounter = 0;
    }
}