int delayTime = 100;
int potPowerPin = 2;
int potPowerOutPin = A1;
int ledPowerPin = 2;
int potPowerOut;
float ledPower;

void setup()
{
    Serial.begin(115200);
    pinMode(ledPowerPin, OUTPUT);
    pinMode(potPowerOutPin, INPUT);
}

void loop()
{
    potPowerOut = analogRead(potPowerOutPin);
    ledPower = map(potPowerOut, 0, 1023, 0, 255);
    analogWrite(ledPowerPin, ledPower);
}