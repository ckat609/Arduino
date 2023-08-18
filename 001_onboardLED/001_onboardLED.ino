int myFunction(int, int);
int pinOutput = 13;
int delayBlink = 1;
int brightness = 1;
int step = 1;

void setup()
{
    Serial.begin(9600);
    pinMode(pinOutput, OUTPUT);
}

void loop()
{
    analogWrite(pinOutput, brightness);

    if (brightness <= 0 || brightness >= 255)
    {
        step = -step;
    }

    brightness = brightness + step;
    delay(delayBlink);
}
