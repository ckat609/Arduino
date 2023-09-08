#include "Controls.h"

const int stepPin = 3;
const int dirPin = 4;
const int greenPin = 7;
const int yellowPin = 8;
const int redPin = 9;
const int photoPin = A2;

// void waitTime(void (*)());

int motoSteps = 200;
int motoStepsDelay = 500;

int gummyCounter = 0;
int gummyCounerGlobal = 0;
int gummyMax = 3;

Led green(greenPin);
Led yellow(yellowPin);
Led red(redPin);

PhotoResistor pr1(photoPin);

void setup()
{
    Serial.begin(115200);

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    pr1.init();
}
void loop()
{
    green.checkBlink();
    yellow.checkBlink();
    red.checkTimeout();

    countCandy();

    if (gummyCounter == gummyMax)
    {
        green.blink(green.SHORT);
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

void countCandy()
{
    if (pr1.triggered())
    {
        red.timeout();
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

        yellow.blink();
        red.clearTimeout();
        gummyCounter++;
        gummyCounerGlobal++;
    }
}
