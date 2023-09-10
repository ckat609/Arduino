#include "Controls.h"

const int stepPin = 3;
const int dirPin = 4;
const int ledGreenPin = 7;
const int ledYellowPin = 8;
const int ledRedPin = 9;
const int photoPin = A2;

// void waitTime(void (*)());

int gummyCounter = 0;
int gummyCounerGlobal = 0;
int gummyMax = 3;

Led ledGreen(ledGreenPin);
Led ledYellow(ledYellowPin);
Led ledRed(ledRedPin);

PhotoResistor pr1(photoPin);

Stepper stepper1(stepPin, dirPin);

void setup()
{
    Serial.begin(115200);

    // pinMode(stepPin, OUTPUT);
    // pinMode(dirPin, OUTPUT);
    pinMode(10, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);

    pr1.init();
}
void loop()
{
    ledRed.blinker(100);
    ledGreen.checkBlink();
    ledYellow.checkBlink();
    ledRed.checkTimeout();
    countCandy();

    if (digitalRead(16) == LOW)
    {
        stepper1.step(stepper1.CCW);
        ledRed.setState(true, "redButton");
    }
    else
    {
        ledRed.setState(false);
    }

    if (digitalRead(10) == LOW)
    {
        stepper1.step(stepper1.CW);
        ledRed.setState(true, "greenButton");
    }
    else
    {
        ledRed.setState(false);
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
    if (pr1.triggered())
    {
        ledRed.timeout();
    }

    if (pr1.passed())
    {
        Serial.print("DULCE: ");
        Serial.print(pr1.getStartValue());
        Serial.print(" - ");
        Serial.print(pr1.read());
        Serial.print(" = ");
        Serial.print(pr1.getStartValue() - pr1.read());
        Serial.print(" ----> CURRENT: ");
        Serial.print(gummyCounter);
        Serial.print(" ----> TOTAL: ");
        Serial.println(gummyCounerGlobal);

        ledYellow.blink();
        ledRed.clearTimeout();
        gummyCounter++;
        gummyCounerGlobal++;
    }

    checkMaxCandy();
}

void checkMaxCandy()
{
    if (gummyCounter == gummyMax)
    {
        ledGreen.blink(ledGreen.SHORT);
        stepper1.cw();

        for (int x = 0; x < 200; x++)
        {
            stepper1.step();
        }
        gummyCounter = 0;
    }
}
