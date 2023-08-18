#define inputSW 3
#define inputCLK 4
#define inputDT 5
#define pinLED 2

int count = 0;
int currentStateSW;
int previousStateSW;
int currentStateCLK;
int previousStateCLK;
int currentStateDT;
int ledValue;
bool isLEDon = true;

void setup()
{
    pinMode(inputSW, INPUT);
    pinMode(inputCLK, INPUT);
    pinMode(inputDT, INPUT);

    pinMode(pinLED, OUTPUT);

    Serial.begin(115200);

    previousStateSW = digitalRead(inputSW);
    previousStateCLK = digitalRead(inputCLK);
}

void loop()
{
    currentStateSW = digitalRead(inputSW);
    currentStateCLK = digitalRead(inputCLK);
    currentStateDT = digitalRead(inputDT);

    if (currentStateCLK != previousStateCLK)
    {
        if (currentStateCLK != digitalRead(inputDT))
        {
            if (count > 0)
                count++;
        }
        else
        {
            if (count < 51)
                count--;
        }
    }

    if (currentStateSW == LOW && previousStateSW == HIGH)
    {
        isLEDon = !isLEDon;
    }
    ledValue = isLEDon ? count : 0;

    previousStateSW = currentStateSW;
    previousStateCLK = currentStateCLK;

    analogWrite(pinLED, count * 5);
}