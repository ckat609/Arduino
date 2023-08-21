#include <LiquidCrystal.h>
#include "keycodes.h"

uint8_t buf[8] = {0}; // Keyboard report buffer

#define LED 12

#define DRE_SW 53
#define DRE_DT 51
#define DRE_CLK 49

#define LCDPIN_RS 3
#define LCDPIN_EN 4
#define LCDPIN_D4 5
#define LCDPIN_D5 6
#define LCDPIN_D6 7
#define LCDPIN_D7 8

#define BUTTON_11 47  // Pin for w
#define BUTTON_12 45  // Pin for a
#define BUTTON_13 43  // Pin for s
#define BUTTON_14 41  // Pin for d
#define BUTTON_PRG 39 // Pin for d

LiquidCrystal lcd(LCDPIN_RS,
                  LCDPIN_EN,
                  LCDPIN_D4,
                  LCDPIN_D5,
                  LCDPIN_D6,
                  LCDPIN_D7);

char lcdTitle[] = "PROGRAM:";

int count = 0;
int LEDValue = 0;
bool isLEDon = true;
int waitShortTime = 5;
int waitLongTime = 250;
int prevTime = 0;

int prevStateBUTTON_PRG;
int currStateBUTTON_PRG;

int currentStateSW;
int previousStateSW;
int currentStateCLK;
int previousStateCLK;
int currentStateDT;

int prevStateBUTTON_11;
int prevStateBUTTON_12;
int prevStateBUTTON_13;
int prevStateBUTTON_14;

const int MAX_KEYS_BOARD = 7;
const int MAX_KEY_SEQ = 7;

typedef struct
{
    int codes[MAX_KEY_SEQ];
} keycode;

typedef struct
{
    char title[16];
    keycode keycodes[MAX_KEYS_BOARD];
    char *keys[MAX_KEYS_BOARD];
    int pins[MAX_KEYS_BOARD];
    int prevStates[MAX_KEYS_BOARD];
} program;

program programs[4] = {{"SCULPT MODE", {{KEYPAD_PLUS}, {KEYPAD_MINUS}, {KEY_CTRL, KEY_TAB, KEYPAD_2}, {KEY_X}, {KEY_SHIFT, KEY_SPACE, KEYPAD_2}, {KEY_G}, {KEY_SHIFT, KEY_SPACE, KEYPAD_6}}, {"+", "-", "Tab", "A", "S", "D", "F"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}},
                       {"TEXTURE PAINT", {{KEYPAD_PLUS}, {KEYPAD_MINUS}, {KEY_CTRL, KEY_TAB, KEYPAD_9}, {KEY_X}, {KEY_SHIFT, KEY_SPACE, KEYPAD_2}, {KEY_G}, {KEY_SHIFT, KEY_SPACE, KEYPAD_6}}, {"+", "-", "Tab", "1", "2", "3", "4"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}},
                       {"VERTEX PAINT", {{KEYPAD_PLUS}, {KEYPAD_MINUS}, {KEY_CTRL, KEY_TAB, KEYPAD_8}, {KEY_X}, {KEY_SHIFT, KEY_SPACE, KEYPAD_2}, {KEY_G}, {KEY_SHIFT, KEY_SPACE, KEYPAD_6}}, {"+", "-", "Tab", "Q", "W", "E", "R"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}},
                       {"WEIGHT PAINT", {{KEYPAD_PLUS}, {KEYPAD_MINUS}, {KEY_CTRL, KEY_TAB, KEYPAD_8}, {KEY_X}, {KEY_SHIFT, KEY_SPACE, KEYPAD_2}, {KEY_G}, {KEY_SHIFT, KEY_SPACE, KEYPAD_6}}, {"+", "-", "Tab", "Q", "W", "E", "R"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}}};

int totalPrograms = (sizeof(programs) / sizeof(programs[0]));
int currentProgram = 0;

void setup()
{
    Serial.begin(9600); // Setup Serial communication

    lcd.begin(16, 2);
    // Set pinmode of Input pins
    for (int i = 0; i < MAX_KEYS_BOARD; i++)
    {
        programs[currentProgram].prevStates[i] = HIGH;
        pinMode(programs[currentProgram].pins[i], INPUT_PULLUP);
        digitalWrite(programs[currentProgram].pins[i], HIGH);
    }

    pinMode(BUTTON_PRG, INPUT_PULLUP);
    digitalWrite(BUTTON_PRG, HIGH);

    pinMode(DRE_SW, INPUT_PULLUP);
    pinMode(DRE_CLK, INPUT);
    pinMode(DRE_DT, INPUT);
    pinMode(LED, OUTPUT);

    previousStateSW = digitalRead(DRE_SW);
    previousStateCLK = digitalRead(DRE_CLK);
    prevTime = millis();
}

void loop()
{

    lcd.setCursor(0, 0);
    lcd.print(programs[currentProgram].title);

    changeProgram(currStateBUTTON_PRG, prevStateBUTTON_PRG, programs, currentProgram, totalPrograms, lcd);

    for (int i = 2; i < MAX_KEYS_BOARD; i++)
    {
        pressKey(programs[currentProgram].pins[i], i, programs[currentProgram].prevStates[i], programs, currentProgram, lcd);
    }

    currentStateSW = digitalRead(DRE_SW);
    currentStateCLK = digitalRead(DRE_CLK);
    currentStateDT = digitalRead(DRE_DT);
    if (currentStateCLK != previousStateCLK)
    {
        if (currentStateCLK != digitalRead(DRE_DT))
        {
            pressKey(DRE_DT, 0, previousStateCLK, programs, currentProgram, lcd);
            if (count > 0)
                count--;
        }
        else
        {
            pressKey(DRE_DT, 1, previousStateCLK, programs, currentProgram, lcd);
            if (count < 51)
                count++;
        }
    }

    if (currentStateSW == LOW && previousStateSW == HIGH)
    {
        pressKey(currentStateSW, 2, previousStateSW, programs, currentProgram, lcd);
        isLEDon = !isLEDon;
    }
    LEDValue = isLEDon ? count * 5 : 0;

    previousStateSW = currentStateSW;
    previousStateCLK = currentStateCLK;

    analogWrite(LED, LEDValue);
}
void releaseKey()
{
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8); // Send Release key
}

void pressKey(int pin, int currKey, int &prevStatePin, program progs[], int currProg, LiquidCrystal &display)
{
    int waitTime = currKey == 0 || currKey == 1 ? waitShortTime : waitLongTime;
    int currTime = millis();

    int currStatePin = digitalRead(pin);
    if (currStatePin == LOW)
    {
        if (currTime - prevTime > waitTime)
        {
            prevTime = currTime;

            for (int i = 0; i < MAX_KEY_SEQ; i++)
            {
                int key = progs[currentProgram].keycodes[currKey].codes[i];
                if (key != 0)
                {
                    if (key == KEY_CTRL || key == KEY_SHIFT || key == KEY_ALT)
                    {
                        buf[0] = key;
                        buf[2] = progs[currentProgram].keycodes[currKey].codes[i + 1];
                        Serial.write(buf, 8); // Send keypress
                        releaseKey();
                        i++;
                    }
                    else
                    {
                        buf[2] = key;
                        Serial.write(buf, 8); // Send keypress
                        releaseKey();
                    }
                }
            }
        }
    }
    prevStatePin = currStatePin;
}

void changeProgram(int &currStatePin, int &prevStatePin, program progs[], int &currProg, int &totalProgs, LiquidCrystal &display)
{
    currStatePin = digitalRead(BUTTON_PRG);
    if (currStatePin == LOW && prevStatePin == HIGH)
    {
        currProg = currProg < totalProgs - 1 ? currProg + 1 : 0;
        display.clear();
    }
    prevStatePin = currStatePin;
}