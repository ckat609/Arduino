
uint8_t buf[8] = {0}; // Keyboard report buffer

#define PIN_W 37 // Pin for w
#define PIN_A 35 // Pin for a
#define PIN_S 33 // Pin for s
#define PIN_D 31 // Pin for d

int prevStatePIN_W;
int prevStatePIN_A;
int prevStatePIN_S;
int prevStatePIN_D;

int currStatePIN_W;
int currStatePIN_A;
int currStatePIN_S;
int currStatePIN_D;

void setup()
{
    Serial.begin(9600); // Setup Serial communication

    // Set pinmode of Input pins
    pinMode(PIN_W, INPUT_PULLUP);
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_S, INPUT_PULLUP);
    pinMode(PIN_D, INPUT_PULLUP);

    digitalWrite(PIN_W, HIGH);
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_S, HIGH);
    digitalWrite(PIN_D, HIGH);
}

void loop()
{
    // When button representing W is pressed
    currStatePIN_W = digitalRead(PIN_W);
    if (currStatePIN_W == LOW && prevStatePIN_W == HIGH)
    {
        buf[2] = 26;          // W keycode
        Serial.write(buf, 8); // Send keypress
        // Serial.println("W");
        releaseKey();
    }
    prevStatePIN_W = currStatePIN_W;

    // When button representing A is pressed
    currStatePIN_A = digitalRead(PIN_A);
    if (currStatePIN_A == LOW && prevStatePIN_A == HIGH)
    {
        buf[2] = 4;           // A keycode
        Serial.write(buf, 8); // Send keypress
        // Serial.println("A");
        releaseKey();
    }
    prevStatePIN_A = currStatePIN_A;

    // When button representing S is pressed
    currStatePIN_S = digitalRead(PIN_S);
    if (currStatePIN_S == LOW && prevStatePIN_S == HIGH)
    {
        buf[2] = 22;          // S keycode
        Serial.write(buf, 8); // Send keypress
        // Serial.println("S");
        releaseKey();
    }
    prevStatePIN_S = currStatePIN_S;

    // When button representing D is pressed
    currStatePIN_D = digitalRead(PIN_D);
    if (currStatePIN_D == LOW && prevStatePIN_D == HIGH)
    {
        buf[2] = 7;           // D keycode
        Serial.write(buf, 8); // Send keypress
        // Serial.println("D");
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
