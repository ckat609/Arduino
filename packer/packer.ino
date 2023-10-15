#include "Button.h"
#include "LED.h"
#include "IR.h"
#include "Stepper.h"
#include "Encoder.h"
#include "Menu.h"

const int stepper1StepPin = 49;
const int stepper1DirPin = 50;
const int stepper1EnablePin = 48;
const int stepper1Ms1Pin = 51;
const int stepper1Ms2Pin = 52;
const int stepper1Ms3Pin = 53;

const int stepper2StepPin = 43;
const int stepper2DirPin = 44;
const int stepper2EnablePin = 42;
const int stepper2Ms1Pin = 45;
const int stepper2Ms2Pin = 46;
const int stepper2Ms3Pin = 47;

const int stepper3StepPin = 37;
const int stepper3DirPin = 38;
const int stepper3EnablePin = 36;
const int stepper3Ms1Pin = 39;
const int stepper3Ms2Pin = 40;
const int stepper3Ms3Pin = 41;

const int stepper4StepPin = 31;
const int stepper4DirPin = 32;
const int stepper4EnablePin = 30;
const int stepper4Ms1Pin = 33;
const int stepper4Ms2Pin = 34;
const int stepper4Ms3Pin = 35;

// const int ledGreenPin = 7;
// const int ledYellowPin = 8;
// const int ledRedPin = 9;

// const int photoPin = 6;

// const int encoderDTPin = 14;
// const int encoderCLKPin = 15;

// const int buttonRedPin = 16;
// const int buttonGreenPin = 10;
const int buttonEncoderPin = 3;
const int buttonLimitResetPin = A0;
const int buttonLimitZeroPin = A1;

// Led ledGreen(ledGreenPin);
// Led ledYellow(ledYellowPin);
// Led ledRed(ledRedPin);

// IR pr1(photoPin);

Stepper stepper1(stepper1StepPin, stepper1DirPin, stepper1EnablePin, stepper1Ms1Pin, stepper1Ms2Pin, stepper1Ms3Pin);
Stepper stepper2(stepper2StepPin, stepper2DirPin, stepper2EnablePin, stepper2Ms1Pin, stepper2Ms2Pin, stepper2Ms3Pin);
Stepper stepper3(stepper3StepPin, stepper3DirPin, stepper3EnablePin, stepper3Ms1Pin, stepper3Ms2Pin, stepper3Ms3Pin);
Stepper stepper4(stepper4StepPin, stepper4DirPin, stepper4EnablePin, stepper4Ms1Pin, stepper4Ms2Pin, stepper4Ms3Pin);

// Encoder encoder1(encoderDTPin, encoderCLKPin);

// Button buttonRed(buttonRedPin);
// Button buttonGreen(buttonGreenPin);
// Button buttonEncoder(buttonEncoderPin);
Button buttonLimitReset(buttonLimitResetPin);
Button buttonLimitZero(buttonLimitZeroPin);

Menu configuration;

void setup()
{
    Serial.begin(115200);

    // pr1.init();
}
void loop()
{
    configuration.rootMenu();

    // ledGreen.check();
    // ledYellow.check();
    // ledRed.check();
    stepper4.move();
    countCandy();

    if (buttonLimitZero.onPress())
    {
        // ledRed.clear();
        // ledGreen.blink(250);
        stepper4.zero();
    }

    if (buttonLimitReset.onPress())
    {
        // ledRed.blinker(100);
        stepper4.reset();
    }

    // if (buttonEncoder.onPress())
    // {
    // configuration.accept();
    // }

    // if (buttonRed.onPress())
    // {
    // }

    // if (buttonRed.onRelease())
    // {
    //     ledRed.blink(250);
    // configuration.previousPage();
    //     stepper1.drop();
    // }

    // if (buttonGreen.onRelease())
    // {
    //     ledRed.blink(250);
    //     configuration.nextPage();
    //     stepper1.home();
    // }
}

void countCandy()
{
    static int gummyCounter = 0;
    static int gummyCounerGlobal = 0;
    static int gummyMax = 3;

    // int checked = pr1.check();

    // if (checked == pr1.TRIGGERED)
    // {
    //     ledRed.timeout();
    // }

    // if (checked == pr1.PASSED)
    // {

    //     ledYellow.blink(ledYellow.BLEEP);
    //     ledRed.clear();
    //     gummyCounter++;
    //     gummyCounerGlobal++;

    //     Serial.print("CURRENT: ");
    //     Serial.print(gummyCounter);
    //     Serial.print(" ----> TOTAL: ");
    //     Serial.println(gummyCounerGlobal);
    // }

    // if (gummyCounter == gummyMax)
    // {
    //     ledGreen.blink(ledGreen.SHORT);
    //     stepper1.funnel();
    //     gummyCounter = 0;
    // }
}