void setup()
{
    Serial.begin(115200);
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop()
{
    delay(1000);
    Serial.println("\nExpression Input: ");
    int len = 0;
    while (1)
    {
        digitalWrite(PC13, HIGH); // turn the LED on (HIGH is the voltage level)
        delay(10);                // wait for a second
        digitalWrite(PC13, LOW);  // turn the LED off by making the voltage LOW
        delay(50);
        for (int i = 0; i < 100; i++)
        {
            char *a = (char *)malloc(1);
        }
        len++;
        Serial.println(len);
    }
}