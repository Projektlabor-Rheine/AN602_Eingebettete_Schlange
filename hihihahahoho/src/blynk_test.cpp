#define BLYNK_USE_DIRECT_CONNECT

#define BLYNK_PRINT Serial

//Blynk login
//Email: erkfry@gmail.com
//Passwort: Harald04


#define M_HERBERT  27 //pins!!!!!!!!!!!!!!
#define M_GUSTAV  18 //pins!!!!!!!!!!!!!!
#define GUSTAV_VOR 19   //pins!!!!!!!!!!!!!!
#define GUSTAV_RUCK 21   //pins!!!!!!!!!!!!!!
#define HERBERT_VOR 26   //pins!!!!!!!!!!!!!!
#define HERBERT_RUCK 25   //pins!!!!!!!!!!!!!!

#define GUSTAV_CHANNEL 0
#define HERBERT_CHANNEL 1

#define PWM_FREQ 50000
#define PWM_RES 8

#define MAX_HEINRICH 0
#define MIN_HEINRICH 0
#define MAX_DIETER 0
#define MIN_DIETER 0


bool gusbert_links = 0;
bool gusbert_rechts = 0;
bool gusbert_vor = 0;
bool gusbert_ruck = 0;

unsigned char pow_herbert = 0;
unsigned char pow_gustav = 0;


#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "lrV8wZVp9RWU_qoTS_gRAbd18sbl103B";

void setup()
{
  // Debug console
  Serial.begin(9600);

    // Anderer KRam
    pinMode(M_HERBERT, OUTPUT);
    pinMode(M_GUSTAV, OUTPUT);
    pinMode(GUSTAV_VOR, OUTPUT);
    pinMode(GUSTAV_RUCK, OUTPUT);
    pinMode(HERBERT_VOR, OUTPUT);
    pinMode(HERBERT_RUCK, OUTPUT);
    

    //PWM
    ledcSetup(GUSTAV_CHANNEL, PWM_FREQ, PWM_RES);
    ledcSetup(HERBERT_CHANNEL, PWM_FREQ, PWM_RES);

    ledcAttachPin(M_GUSTAV, GUSTAV_CHANNEL);
    ledcAttachPin(M_HERBERT, HERBERT_CHANNEL);

    ledcWrite(GUSTAV_CHANNEL, pow_gustav);
    ledcWrite(HERBERT_CHANNEL, pow_herbert);


  //Blynk etup
  Serial.println("Waiting for connections...");
  Blynk.setDeviceName("MakieDerKiller");

  Blynk.begin(auth);
}

void loop()
{
  Blynk.run();
}


void update_gusbert(){
    if(gusbert_vor || gusbert_ruck) {
        pow_herbert = 255;
        pow_gustav = 255;
    }else {
        pow_herbert = 0;
        pow_gustav = 0;
    }

    if(gusbert_links) {
        pow_gustav = pow_gustav >> 1;
    }

    if(gusbert_rechts) {
        pow_herbert = pow_herbert >> 1;
    }

    if(gusbert_vor && gusbert_ruck || !gusbert_vor && !gusbert_ruck) {
        digitalWrite(GUSTAV_VOR, 0);
        digitalWrite(GUSTAV_RUCK, 0);
        digitalWrite(HERBERT_VOR, 0);
        digitalWrite(HERBERT_RUCK, 0);
        
    } else if (gusbert_vor) {
        digitalWrite(GUSTAV_RUCK, 0);
        digitalWrite(HERBERT_RUCK, 0);
        delayMicroseconds(500);
        digitalWrite(GUSTAV_VOR, 1);
        digitalWrite(HERBERT_VOR, 1);
    } else if (gusbert_ruck) {
        digitalWrite(GUSTAV_VOR, 0);
        digitalWrite(HERBERT_VOR, 0);
        delayMicroseconds(500);
        digitalWrite(GUSTAV_RUCK, 1);
        digitalWrite(HERBERT_RUCK, 1);
    }


    ledcWrite(GUSTAV_CHANNEL, pow_gustav);
    ledcWrite(HERBERT_CHANNEL, pow_herbert);
}


BLYNK_WRITE(V0) //Vor
{
    gusbert_vor = param.asInt();
    update_gusbert();
}


BLYNK_WRITE(V1) //Ruck
{
    gusbert_ruck = param.asInt();
    update_gusbert();
}


BLYNK_WRITE(V3) //Links
{
  gusbert_links = param.asInt();
  update_gusbert();
}

BLYNK_WRITE(V4) //Rechts
{
  gusbert_rechts = param.asInt();
  update_gusbert();
}

BLYNK_WRITE(V2) //Joystick der Verdammnis
{
  int x = param[0].asInt(); // getting first value
  int y = param[1].asInt(); // getting second value
}
