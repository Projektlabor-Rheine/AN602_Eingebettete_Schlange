#include<Arduino.h>

#define OUT 25
#define S3 27
#define S2 26
#define OE 5

#define S1 33
#define S0 32

int64_t s = 0;
int64_t sa = 0;
int64_t i = 0;

void IRAM_ATTR I ()
{ 
    i += 1;
}

void setup2()
{
    Serial.begin(115200);
    
    pinMode(OE, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(OUT, INPUT_PULLUP);
    pinMode(S1, OUTPUT);
    pinMode(S0, OUTPUT);


    digitalWrite(OE, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S0, HIGH);

 
  attachInterrupt(digitalPinToInterrupt(OUT), I, FALLING);
}

void loop2()
{

    s += 1;

    if (s >= 50)
    {
        Serial.println(i);
        if (i <= 2800)
        {
        Serial.println("sop");
          
        }
        i = 0;
        s = 0;
    }
    delay(1);

}