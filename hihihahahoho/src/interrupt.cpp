/*#include <Arduino.h>

int OMotorR = 14;
int OMotorL = 13;

const int freq = 50000;
const int ledChannel = 0;
const int resolution = 8;
const int ledChannelII = 1;

//int EncoderRI = 33;
const byte EncoderRI = 33;
//int EncoderLI = 32;
const byte EncoderLI = 32;


volatile unsigned long LI = 0;
volatile unsigned long LII = 0;
volatile unsigned long RI = 0;
volatile unsigned long RII = 0;

volatile long eL = 0;
volatile long eR = 0;
long e  = 0;
int E  = 0;
int I;
int p;
int d;
int pwm = 0;

int MotorL;
int MotorR;
int ruckwartsL = 12;
int fortwartsL = 14;
int ruckwartsR = 1;
int fortwartsR = 13;

void IRAM_ATTR IEL ()
{
  LII = LI;
  LI = millis();
  eL = LI - LII;
}

void IRAM_ATTR IER ()
{ 
  RII = RI;
  RI = millis();   
  eR = RI - RII;
}


void setup() {
  Serial.begin(115200);
  pinMode(EncoderRI, INPUT_PULLUP);
  pinMode(EncoderLI, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EncoderRI), IER, FALLING);
  attachInterrupt(digitalPinToInterrupt(EncoderLI), IEL, FALLING);



  I = 0;
  p = 0;
  MotorL = 0;
  MotorR = 0;

  pinMode(OMotorR, OUTPUT);
  pinMode(OMotorL, OUTPUT);
  pinMode(ruckwartsL, OUTPUT);
  pinMode(ruckwartsR, OUTPUT);
  pinMode(fortwartsL, OUTPUT);
  pinMode(fortwartsR, OUTPUT);

    
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(OMotorR, ledChannel);
  ledcAttachPin(OMotorL, ledChannelII);
}



void loop()
{


 // E =  e;




  //Regeleung
  e  =eR - eL;
  Serial.println(eR + "R");
  Serial.println(eL + "L");
  Serial.println(e + "e");
  //I = e; 
  p = e<<3;
  //d = e - E;

  pwm = I + p + d;
    Serial.println(pwm + "pwm");

    MotorL += pwm;
    delay(20);

    if (MotorL < 0)
    {
      digitalWrite(fortwartsL, HIGH);
      digitalWrite(ruckwartsL, LOW);
    }
    else if (MotorL > 0)
    {
      digitalWrite(fortwartsL, LOW);
      digitalWrite(ruckwartsL, HIGH);
    }
    else 
    {
      digitalWrite(ruckwartsL, HIGH);
      digitalWrite(fortwartsL, HIGH);
    }



    ledcWrite(ledChannelII, abs(MotorL));

    delay(10);

}*/