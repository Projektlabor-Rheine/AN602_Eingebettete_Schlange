// #include <Arduino.h>
// #include <ESP32Servo.h>


// //IrV8wZVp9RWU_qoTS_gRAbd18sbl103B


// //Input Only Pins 34 35 36 39

// Servo Kippen;
// Servo Drehen;

// int minUs = 1000;
// int maxUs = 2000;

// short ServoDD = 0;
// short ServoKK = 0;

// const int32_t freq = 50000;
// const int32_t ledChannel = 0;
// const int32_t resolution = 8;
// const int32_t ledChannelII = 1;
// #define OMotorL  27 //pins!!!!!!!!!!!!!!
// #define OMotorR  18 //pins!!!!!!!!!!!!!!
// #define RR 19   //pins!!!!!!!!!!!!!!
// #define VR 21   //pins!!!!!!!!!!!!!!
// #define RL 26   //pins!!!!!!!!!!!!!!
// #define VL 25   //pins!!!!!!!!!!!!!!
// int32_t pwm = 0; //0-255
// String Motor = "";
// bool richtung = 0;
// String ServoStr = "";
// int32_t Grad = 0;
// int32_t ServoD = 0;
// int32_t ServoK = 0;
// int32_t MotorR = 0;
// boolean ruckwartsR = false;
// boolean ruckwartsL = false;
// int32_t MotorL  = 0;


// void setupasd()
// {
//   Serial.begin(115200);
//   ledcSetup(ledChannel, freq, resolution);
//   ledcSetup(ledChannelII, freq, resolution);

//   ledcAttachPin(OMotorR, ledChannel);
//   ledcAttachPin(OMotorL, ledChannelII);

//   Kippen.setPeriodHertz(50);      // Standard 50hz servo
//   Drehen.setPeriodHertz(50); 

//   pinMode(VR, OUTPUT);
//   pinMode(RR, OUTPUT);
//   pinMode(VL, OUTPUT);
//   pinMode(RL, OUTPUT);
        
// }



// void ServSte()
// {
//     Kippen.attach(14, minUs, maxUs); //pins!!!!!!!!!!!!!!
//     Drehen.attach(23, minUs, maxUs); //pins!!!!!!!!!!!!!!

//      if (ServoK != 0 )
//     {
//         ServoKK += ServoK;
//         if (ServoKK <= 180)
//         {
            
//             Kippen.write(ServoKK); 
//         }
//         else
//         {
//             ServoKK = 180;
//         }
//        ServoK = 0;
//     }
//     if (ServoD != 0)
//     {
//         ServoDD += ServoD;
//         if (ServoDD <= 180)
//         {
            
//             Drehen.write(ServoDD); 
//         }
//         else
//         {
//             ServoKK = 180;
//         }
//        ServoD = 0;
//     } 
    
//     ServoStr = "";
// }

// void MotStr ()
// {

//     if (ruckwartsL == true)
//     {

//         digitalWrite(VL, LOW);
//         delay(1);
//         digitalWrite(RL, HIGH);
        
//     }
//     else 
//     {
//         digitalWrite(RL, LOW);
//         delay(1);
//         digitalWrite(VL, HIGH);
//     }
    
//     if (ruckwartsR == true)
//     {
//         digitalWrite(VR, LOW);
//         delay(1);
//         digitalWrite(RR, HIGH);

//     }
//     else 
//     {
//         digitalWrite(RR, LOW);
//         delay(1);
//         digitalWrite(VR, HIGH);
//     }   

//     ledcWrite(ledChannel, MotorR);

//     ledcWrite(ledChannelII, MotorL);
//     Motor = "";
// }

// void SerRead()
// {

//     while (Serial.available()) // M<>,<pwm>,<Richtung>    getrennt S<>,<Grad>
//     {  
//         Serial.println("seread");
//         Motor = Serial.readStringUntil(','); // Motorwhl M<1/0>
//         pwm = Serial.parseInt(); // irgendwas zwischen 0 - 255
//         richtung = Serial.parseInt(); // 0 vorwärts 1 rückwärts 
           
//        /* ServoStr = Serial.readStringUntil(','); // Servowhl S<1/0>
//         Grad = Serial.parseInt();//Servograddrehzahl 0 - 180
       
       
//         if (ServoStr == "S1")
//         {
//         ServoD = Grad;
//         }
//         else if (ServoStr == "S0")
//         {
//          ServoK = Grad;
//         }*/

//         if (Motor == "M1")
//         {
//             MotorR = pwm;
//             if (richtung == 1)
//             {
//                 ruckwartsR = true;
//             }
//             else
//             {
//                 ruckwartsR = false;
//             }
//         }
//         else if (Motor == "M0")
//         {
//             Serial.println("uwu");
//             MotorL = pwm;
//             if (richtung == 1)
//             {
//                 ruckwartsL = true;
//             }
//             else
//             {
//                 ruckwartsL = false;
//             }
//         }
        
//     }
// }

// void loopasd()
// {
//     //Serial.println("loop");
//     SerRead();
    
//     if (ServoStr != "")
//     {
//         ServSte();
//     }
//         if (Motor != "")
//     {
//         MotStr();
//     }

// }
  
