const int stepPin = 3;
const int dirPin = 4;
const int ledPin = A3;
const int photoPin = A2;

unsigned long photoStartTime = millis();
int photoStartVal;
int photoCurrentVal;
int photoSensitivity = 100;
int photoWait = 500;
int motoSteps = 200;
int motoStepsDelay = 500;
bool isLedOn = false;

int gummyCounter = 0;
int gummyCounerGlobal = 0;
int gummyMax = 3;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    photoStartVal = analogRead(photoPin);
}
void loop()
{
    photoCurrentVal = analogRead(photoPin);

    if (millis() - photoStartTime >= photoWait && photoStartVal - photoCurrentVal > photoSensitivity)
    {

        Serial.print("DULCE: ");
        Serial.print(photoStartVal);
        Serial.print(" - ");
        Serial.print(photoCurrentVal);
        Serial.print(" = ");
        Serial.print(photoStartVal - photoCurrentVal);
        Serial.print(" ----> TOTAL: ");
        Serial.println(gummyCounerGlobal);

        gummyCounter++;
        gummyCounerGlobal++;
        photoStartTime = millis();
    }

    if (gummyCounter == gummyMax)
    {
        bool inLoop = true;
        digitalWrite(ledPin, HIGH);
        digitalWrite(dirPin, HIGH);

        for (int x = 0; x < motoSteps; x++)
        {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(motoStepsDelay);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(motoStepsDelay);
        }
        gummyCounter = 0;
        digitalWrite(ledPin, LOW);
    }
}