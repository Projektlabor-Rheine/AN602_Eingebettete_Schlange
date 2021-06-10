/*#include <Arduino.h>
#include <ESP32Encoder.h>


ESP32Encoder SMotorR;
ESP32Encoder SMotorL;

// timer and flag for example, not needed for encoders
unsigned long SMotorLlastToggled;
bool SMotorLPaused = false;

int OMotorR = 14;
int OMotorL = 15;

const int freq = 50000;
const int ledChannel = 0;
const int resolution = 8;
const int ledChannelII = 1;

int pwm; //0-255



int e;
int i; 
int p;

int MotorL;
int MotorR;
int ruckwartsL = 4;
int fortwartsL = 1;
int ruckwartsR = 2;
int fortwartsR = 13;
int Differenzzaehler;

int RR; //rückwartsrehcts 
int LR;

void setup()
{
  i= 0;
  p = 0;
  MotorL = 0;
  MotorR = 0;

  Serial.begin(115200);
  ESP32Encoder::useInternalWeakPullResistors=UP;ESP32Encoder::useInternalWeakPullResistors=UP;

    // use pin 19 and 18 for the first encoder
	SMotorR.attachHalfQuad(19, 18);
	// use pin 17 and 16 for the second encoder
	SMotorL.attachHalfQuad(17, 16);
    // set starting count value after attaching
	SMotorR.setCount(0);
    // clear the encoder's raw count and set the tracked count to zero
	SMotorL.clearCount();
	//Serial.println("Encoder Start = " + String((int32_t)SMotorR.getCount()));
	// set the lastToggle
	SMotorLlastToggled = millis();
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



  if (RR == 0 && LR == 0 || RR == 1 && LR == 1)
  {
      
    e = SMotorR.getCount() - SMotorL.getCount();
      
    Serial.println(e);
    //Serial.println(String((int32_t)SMotorR.getCount()) + "  " + String((int32_t)SMotorL.getCount()));
      
    i -= e;
    p = -(e<<3);
    MotorL = p + i; 


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

    if (RR == 0 && LR == 0)
    {
      digitalWrite(fortwartsR, HIGH);
      digitalWrite(ruckwartsR, LOW);
    }
    else 
    {
      digitalWrite(fortwartsR, LOW);
      digitalWrite(ruckwartsR, HIGH);
    }

    ledcWrite(ledChannelII, abs(MotorL));
    SMotorL.clearCount();
    SMotorR.clearCount();
    delay(10);
  }
  else if ( RR == 0 && LR == 1 || RR == 1 && LR == 0)
  {
    e = SMotorR.getCount() + SMotorL.getCount();
    
    Serial.println(e);
	  //Serial.println(String((int32_t)SMotorR.getCount()) + "  " + String((int32_t)SMotorL.getCount()));
     
    

    if (RR == 0 && LR == 1)
    {


      i -= e;
      p = -(e<<3); //bitshciften ezentiell mal 6 rechnen 3*2
      MotorL = (p + i); 


      if (MotorL > 0)
      {
        digitalWrite(fortwartsL, HIGH);
        digitalWrite(ruckwartsL, LOW);
      }
      else if (MotorL < 0)
      {
        digitalWrite(fortwartsL, LOW);
        digitalWrite(ruckwartsL, HIGH);
      }
      else 
      {
        digitalWrite(ruckwartsL, HIGH);
        digitalWrite(fortwartsL, HIGH);
      }

      digitalWrite(fortwartsR, HIGH);
      digitalWrite(ruckwartsR, LOW);
    }
    else if (RR == 1 && LR == 0)
    {

      
      i += e;
      p = +(e<<3); //bitshciften ezentiell mal 6 rechnen 3*2
      MotorL = (p + i); 


      if (MotorL > 0)
      {
        digitalWrite(fortwartsL, HIGH);
        digitalWrite(ruckwartsL, LOW);
      }
      else if (MotorL < 0)
      {
        digitalWrite(fortwartsL, LOW);
        digitalWrite(ruckwartsL, HIGH);
      }
      else 
      {
        digitalWrite(ruckwartsL, HIGH);
        digitalWrite(fortwartsL, HIGH);
      }

      digitalWrite(fortwartsR, LOW);
      digitalWrite(ruckwartsR, HIGH);
    }
    ledcWrite(ledChannelII, abs(MotorL));
    SMotorL.clearCount();
    SMotorR.clearCount();
    delay(10);

  }
  e = SMotorR.getCount() - SMotorL.getCount();
      
    Serial.println(e);
    //Serial.println(String((int32_t)SMotorR.getCount()) + "  " + String((int32_t)SMotorL.getCount()));
      
    i -= e;
    p = -(e<<3);
    MotorL = p + i; 


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
    SMotorL.clearCount();
    SMotorR.clearCount();
    delay(10);

}*/