int ledPin = 3;
int pbReadPin = 2;
bool ledState = false;
bool currButtonUp = true;
bool prevButtonUp = true;
int delayTime = 50;

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(pbReadPin, INPUT);
    Serial.begin(115200);
}

void loop()
{
    currButtonUp = digitalRead(pbReadPin);

    if (currButtonUp && !prevButtonUp)
    {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
    }

    prevButtonUp = currButtonUp;
    delay(delayTime);
}
