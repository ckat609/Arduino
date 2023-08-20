#include <LiquidCrystal.h>

uint8_t buf[8] = {0}; // Keyboard report buffer

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

const int MAXKEYS = 4;
typedef struct
{
    char *title;
    int keycodes[MAXKEYS];
    char keys[MAXKEYS];
    int pins[MAXKEYS];
} program;

program programs[3] = {{"SCULPT MODE", {4, 22, 7, 9}, {'A', 'S', 'D', 'F'}},
                       {"TEXTURE PAINT", {30, 31, 32, 33}, {'1', '2', '3', '4'}},
                       {"GREASE PENCIL", {20, 26, 8, 21}, {'Q', 'W', 'E', 'R'}}};

char lcdTitle[] = "PROGRAM:";
// char *programs[3] = {"SCULPT MODE", "TEXTURE PAINT", "GREASE PENCIL"};
int totalPrograms = (sizeof(programs) / sizeof(programs[0]));
int currentProgram = 0;

int prevStateBUTTON_11;
int prevStateBUTTON_12;
int prevStateBUTTON_13;
int prevStateBUTTON_14;
int prevStateBUTTON_PRG;

int currStateBUTTON_11;
int currStateBUTTON_12;
int currStateBUTTON_13;
int currStateBUTTON_14;
int currStateBUTTON_PRG;

void setup()
{
    Serial.begin(9600); // Setup Serial communication

    lcd.begin(16, 2);
    // Set pinmode of Input pins
    pinMode(BUTTON_11, INPUT_PULLUP);
    pinMode(BUTTON_12, INPUT_PULLUP);
    pinMode(BUTTON_13, INPUT_PULLUP);
    pinMode(BUTTON_14, INPUT_PULLUP);
    pinMode(BUTTON_PRG, INPUT_PULLUP);

    digitalWrite(BUTTON_11, HIGH);
    digitalWrite(BUTTON_12, HIGH);
    digitalWrite(BUTTON_13, HIGH);
    digitalWrite(BUTTON_14, HIGH);
    digitalWrite(BUTTON_PRG, HIGH);
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print(lcdTitle);
    lcd.setCursor(0, 1);
    lcd.print(programs[currentProgram].title);

    changeProgram(currStateBUTTON_PRG, prevStateBUTTON_PRG, programs, currentProgram, totalPrograms, lcd);
    pressKey(BUTTON_11, 0, currStateBUTTON_11, prevStateBUTTON_11, programs, currentProgram);
    pressKey(BUTTON_12, 1, currStateBUTTON_12, prevStateBUTTON_12, programs, currentProgram);
    pressKey(BUTTON_13, 2, currStateBUTTON_13, prevStateBUTTON_13, programs, currentProgram);
    pressKey(BUTTON_14, 3, currStateBUTTON_14, prevStateBUTTON_14, programs, currentProgram);
}
// Function for Key Release
void releaseKey()
{
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8); // Send Release key
}

void pressKey(int pin, int currKey, int &currStatePin, int &prevStatePin, program progs[], int currProg)
{
    currStatePin = digitalRead(pin);
    if (currStatePin == LOW && prevStatePin == HIGH)
    {
        buf[2] = progs[currentProgram].keycodes[currKey]; // keycode
        Serial.write(buf, 8);                             // Send keypress
        releaseKey();
        // Serial.println(progs[currentProgram].key[currKey]);
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