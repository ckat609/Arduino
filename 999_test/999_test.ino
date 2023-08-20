#include <LiquidCrystal.h>

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

const int MAXKEYS = 7;
typedef struct
{
    char *title;
    int keycodes[MAXKEYS];
    char *keys[MAXKEYS];
    int pins[MAXKEYS];
    int prevStates[MAXKEYS];
} program;

program programs[3] = {{"SCULPT MODE", {87, 86, 43, 4, 22, 7, 9}, {"+", "-", "Tab", "A", "S", "D", "F"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}},
                       {"TEXTURE PAINT", {87, 86, 43, 30, 31, 32, 33}, {"+", "-", "Tab", "1", "2", "3", "4"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}},
                       {"GREASE PENCIL", {87, 86, 43, 20, 26, 8, 21}, {"+", "-", "Tab", "Q", "W", "E", "R"}, {DRE_CLK, DRE_CLK, DRE_SW, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14}, {previousStateCLK, previousStateCLK, previousStateSW, prevStateBUTTON_11, prevStateBUTTON_12, prevStateBUTTON_13, prevStateBUTTON_14}}};

int totalPrograms = (sizeof(programs) / sizeof(programs[0]));
int currentProgram = 0;

void setup()
{
    Serial.begin(9600); // Setup Serial communication

    lcd.begin(16, 2);
    // Set pinmode of Input pins
    for (int i = 0; i < MAXKEYS; i++)
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
}

void loop()
{

    lcd.setCursor(0, 0);
    lcd.print(lcdTitle);
    lcd.setCursor(0, 1);
    lcd.print(programs[currentProgram].title);

    changeProgram(currStateBUTTON_PRG, prevStateBUTTON_PRG, programs, currentProgram, totalPrograms, lcd);

    for (int i = 2; i < MAXKEYS; i++)
    {
        pressKey(programs[currentProgram].pins[i], i, programs[currentProgram].prevStates[i], programs, currentProgram);
    }

    currentStateSW = digitalRead(DRE_SW);
    currentStateCLK = digitalRead(DRE_CLK);
    currentStateDT = digitalRead(DRE_DT);
    if (currentStateCLK != previousStateCLK)
    {
        if (currentStateCLK != digitalRead(DRE_DT))
        {
            pressKey(DRE_DT, 0, previousStateCLK, programs, currentProgram);
            if (count > 0)
                count--;
        }
        else
        {
            pressKey(DRE_DT, 1, previousStateCLK, programs, currentProgram);
            if (count < 51)
                count++;
        }
    }

    if (currentStateSW == LOW && previousStateSW == HIGH)
    {
        pressKey(currentStateSW, 2, previousStateSW, programs, currentProgram);
        isLEDon = !isLEDon;
    }
    LEDValue = isLEDon ? count * 5 : 0;

    previousStateSW = currentStateSW;
    previousStateCLK = currentStateCLK;

    analogWrite(LED, LEDValue);
}
// Function for Key Release
void releaseKey()
{
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8); // Send Release key
}

void pressKey(int pin, int currKey, int &prevStatePin, program progs[], int currProg)
{
    int currStatePin = digitalRead(pin);
    if (currStatePin == LOW)
    {
        buf[2] = progs[currentProgram].keycodes[currKey]; // keycode
        Serial.write(buf, 8);                             // Send keypress
        releaseKey();
        // Serial.print("KEYCODE: ");#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J#J
        // Serial.print(progs[currentProgram].keycodes[currKey]);
        // Serial.print(" - KEY: ");
        // Serial.println(progs[currentProgram].keys[currKey]);
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
        // Serial.println(progs[currProg].title); // Print the selected program
    }
    prevStatePin = currStatePin;
}