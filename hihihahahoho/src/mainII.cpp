/*
#include <Arduino.h>
#include <ESP32Encoder.h>
#include <ESP32Servo.h>


String MotorStr = "";
String ServoStr  = "";
bool richtung;

Servo Kippen;
Servo Drehen;

int minUs = 1000;
int maxUs = 2000;

short ServoDD = 0;
short ServoKK = 0;

int Grad = 0;
int ServoD = 0;
int ServoK = 0;

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

int pwm = 0; //0-255



int e;
int i; 
int p;

int MotorL;
int MotorR;
int ruckwartsL = 4;
int fortwartsL = 2;
int ruckwartsR = 1;
int fortwartsR = 13;
int Differenzzaehler;

int RR = 0; //rückwartsrehcts 
int LR = 0;

void setup()
{

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
	Kippen.setPeriodHertz(50);      // Standard 50hz servo
	Drehen.setPeriodHertz(50); 


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
  while (Serial.available()) // M<>,<pwm>,<Richtung>    getrennt S<>,<Grad>
  {  
    MotorStr = Serial.readStringUntil(','); // Motorwhl M<1/0>
    if ( MotorStr == "M1" || MotorStr == "M0"  )
    {
      
      pwm = Serial.parseInt(); // irgendwas zwischen 0 - 255
      richtung = Serial.parseInt(); // 0 vorwärts 1 rückwärts 
      Serial.println("MMMMMMMM");
      if (MotorStr == "M1")
      {
        MotorR = pwm;
        Serial.println("MMMMMMMM11111ppppppwwwwmmmmm");
        ledcWrite(ledChannel, abs(MotorR));

        if (richtung == 1)
        {
          digitalWrite(fortwartsR, LOW);
          digitalWrite(ruckwartsR, HIGH);
        }
        else
        {
          digitalWrite(fortwartsR, HIGH);
          digitalWrite(ruckwartsR, LOW);
        }
      }
      else if (MotorStr == "M0")
      {
        Serial.println("MMMMMMMM000000ppppppwwwwmmmmm");
        MotorL = pwm;
        ledcWrite(ledChannelII, abs(MotorL));
        if (richtung == 1)
        {
          digitalWrite(fortwartsL, LOW);
          digitalWrite(ruckwartsL, HIGH);
        }
        else
        {
          digitalWrite(fortwartsL, HIGH);
          digitalWrite(ruckwartsL, LOW);
        }
      }
          
    }
    else if (MotorStr == "S1" || MotorStr == "S0"  )
    {
      //ServoStr = Serial.readStringUntil(','); // Servowhl S<1/0>
      Grad = Serial.parseInt();//Servograddrehzahl 0 - 180

      if (ServoStr == "S1")
      {
      ServoD = Grad;
      }
      else if (ServoStr == "S0")
      {
      ServoK = Grad;
      }
    }
    else
    {
      break;
    }
      
      

      
      
  }


  if( ServoK != 0 || ServoD != 0 )
  {
    Kippen.attach(0, minUs, maxUs);
    Drehen.attach(4, minUs, maxUs);

    if (ServoK != 0 )
    {
      ServoKK += ServoK;
      if (ServoKK <= 180)
      {
          
        Kippen.write(ServoKK); 
      }
      else
      {
        ServoKK = 180;
      }
      ServoK = 0;
    }

    if (ServoD != 0)
    {
      ServoDD += ServoD;
      if (ServoDD <= 180)
      {
          
        Drehen.write(ServoDD); 
      }
      else
      {
        ServoKK = 180;
      }
      ServoD = 0;
    }
    //delay(15);
  }

  if (RR == 0 && LR == 0 || RR == 1 && LR == 1)
  {
      
    e = SMotorR.getCount() - SMotorL.getCount();
      
    Serial.println(e);
    //Serial.println(String((int32_t)SMotorR.getCount()) + "  " + String((int32_t)SMotorL.getCount()));
      
    i -= e;
    Serial.println(i + "I");
    p = -(e<<3);
    Serial.println(p + "P");
    MotorL = p + i; 
    delay(15);

   // Serial.println(MotorL + "l");

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
    //delay(10);
    Serial.println("lol");
  }
  

}*/