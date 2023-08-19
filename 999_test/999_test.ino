#include <LiquidCrystal.h>

uint8_t buf[8] = {0}; // Keyboard report buffer

#define LCDPIN_RS 3
#define LCDPIN_EN 4
#define LCDPIN_D4 5
#define LCDPIN_D5 6
#define LCDPIN_D6 7
#define LCDPIN_D7 8

#define PIN_W 47       // Pin for w
#define PIN_A 45       // Pin for a
#define PIN_S 43       // Pin for s
#define PIN_D 41       // Pin for d
#define PIN_PRG_CHG 39 // Pin for d

LiquidCrystal lcd(LCDPIN_RS,
                  LCDPIN_EN,
                  LCDPIN_D4,
                  LCDPIN_D5,
                  LCDPIN_D6,
                  LCDPIN_D7);

char lcdTitle[] = "PROGRAM:";
char *programs[3] = {"SCULPT MODE", "TEXTURE PAINT", "GREASE PENCIL"};
int totalPrograms = (sizeof(programs) / sizeof(programs[0]));
int currentProgram = 0;

int prevStatePIN_W;
int prevStatePIN_A;
int prevStatePIN_S;
int prevStatePIN_D;
int prevStatePIN_PRG_CHG;

int currStatePIN_W;
int currStatePIN_A;
int currStatePIN_S;
int currStatePIN_D;
int currStatePIN_PRG_CHG;

void setup()
{
    Serial.begin(115200); // Setup Serial communication

    lcd.begin(16, 2);
    // Set pinmode of Input pins
    pinMode(PIN_W, INPUT_PULLUP);
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_S, INPUT_PULLUP);
    pinMode(PIN_D, INPUT_PULLUP);
    pinMode(PIN_PRG_CHG, INPUT_PULLUP);

    digitalWrite(PIN_W, HIGH);
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_S, HIGH);
    digitalWrite(PIN_D, HIGH);
    digitalWrite(PIN_PRG_CHG, HIGH);
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print(lcdTitle);
    lcd.setCursor(0, 1);
    lcd.print(programs[currentProgram]);

    // When program change button is pressed
    // currStatePIN_PRG_CHG = digitalRead(PIN_PRG_CHG);
    // if (currStatePIN_PRG_CHG == LOW && prevStatePIN_PRG_CHG == HIGH)
    // {
    //     currentProgram = currentProgram < totalPrograms - 1 ? currentProgram + 1 : 0;
    //     lcd.clear();
    //     Serial.println(programs[currentProgram]);
    // }
    // prevStatePIN_PRG_CHG = currStatePIN_PRG_CHG;

    changeProgram(programs, currentProgram, totalPrograms, currStatePIN_PRG_CHG, prevStatePIN_PRG_CHG, lcd);

    // When button representing W is pressed
    currStatePIN_W = digitalRead(PIN_W);
    if (currStatePIN_W == LOW && prevStatePIN_W == HIGH)
    {
        buf[2] = 26;          // W keycode
        Serial.write(buf, 8); // Send keypress
        Serial.println("W");
        releaseKey();
    }
    prevStatePIN_W = currStatePIN_W;

    // When button representing A is pressed
    currStatePIN_A = digitalRead(PIN_A);
    if (currStatePIN_A == LOW && prevStatePIN_A == HIGH)
    {
        buf[2] = 4;           // A keycode
        Serial.write(buf, 8); // Send keypress
        Serial.println("A");
        releaseKey();
    }
    prevStatePIN_A = currStatePIN_A;

    // When button representing S is pressed
    currStatePIN_S = digitalRead(PIN_S);
    if (currStatePIN_S == LOW && prevStatePIN_S == HIGH)
    {
        buf[2] = 22;          // S keycode
        Serial.write(buf, 8); // Send keypress
        Serial.println("S");
        releaseKey();
    }
    prevStatePIN_S = currStatePIN_S;

    // When button representing D is pressed
    currStatePIN_D = digitalRead(PIN_D);
    if (currStatePIN_D == LOW && prevStatePIN_D == HIGH)
    {
        buf[2] = 7;           // D keycode
        Serial.write(buf, 8); // Send keypress
        Serial.println("D");
        releaseKey();
    }
    prevStatePIN_D = currStatePIN_D;
}
// Function for Key Release
void releaseKey()
{
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8); // Send Release key
}

void changeProgram(char *progs[], int &currProg, int &totalProgs, int &currStatePin, int &prevStatePin, LiquidCrystal &display)
{
    currStatePin = digitalRead(PIN_PRG_CHG);
    if (currStatePin == LOW && prevStatePin == HIGH)
    {
        currProg = currProg < totalProgs - 1 ? currProg + 1 : 0;
        display.clear();
        Serial.println(progs[currProg]);
    }
    prevStatePin = currStatePin;
}