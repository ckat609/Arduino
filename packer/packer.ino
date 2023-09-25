#include "Button.h"
#include "LED.h"
#include "IR.h"
#include "Stepper.h"
#include "Encoder.h"

const int stepperStepPin = 3;
const int stepperDirPin = 4;

const int ledGreenPin = 7;
const int ledYellowPin = 8;
const int ledRedPin = 9;

const int photoPin = 6;

const int encoderDTPin = 14;
const int encoderCLKPin = 15;

const int buttonRedPin = 16;
const int buttonGreenPin = 10;
const int buttonEncoderPin = 5;
const int buttonLimitResetPin = A0;
const int buttonLimitZeroPin = A1;

Led ledGreen(ledGreenPin);
Led ledYellow(ledYellowPin);
Led ledRed(ledRedPin);

IR pr1(photoPin);

Stepper stepper1(stepperStepPin, stepperDirPin);

Encoder encoder1(encoderDTPin, encoderCLKPin);

Button buttonRed(buttonRedPin);
Button buttonGreen(buttonGreenPin);
Button buttonEncoder(buttonEncoderPin);
Button buttonLimitReset(buttonLimitResetPin);
Button buttonLimitZero(buttonLimitZeroPin);

void setup()
{
    Serial.begin(115200);

    pr1.init();
}
void loop()
{
    ledGreen.check();
    ledYellow.check();
    ledRed.check();
    stepper1.move();
    countCandy();

    // ledRed.blinker(150);
    if (buttonLimitZero.onPress())
    {
        ledRed.clear();
        ledGreen.blink(250);
        stepper1.zero();
    }

    if (buttonLimitReset.onPress())
    {
        ledRed.blinker(150);
        stepper1.reset();
    }

    if (buttonEncoder.onPress())
    {
    }

    if (buttonRed.onPress())
    {
        ledYellow.blink(50);
    }

    if (buttonRed.onRelease())
    {
        ledRed.blink(50);
        stepper1.drop();
    }

    if (buttonGreen.onRelease())
    {
        ledRed.blink(50);
        stepper1.home();
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