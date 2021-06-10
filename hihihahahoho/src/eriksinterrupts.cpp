/*
#include <Arduino.h>
#include <Wire.h>

#define ENC_1 33
#define ENC_2 32
#define OUT_PIN 13


volatile uint64_t enc_1_last = 0;
volatile uint64_t enc_1_period = 2000;

volatile uint64_t enc_2_last = 0;
volatile uint64_t enc_2_period = 2000;


int32_t reg_e[8];
uint8_t reg_e_i = 0;
int32_t reg_e_II[8];
uint8_t reg_e_i_II = 0;


uint32_t reg_e_av();

uint32_t reg_e_av_II();

uint32_t last_sp = 0;
uint64_t l_sp = 0;


void IRAM_ATTR ENC_1_ISR() 
{
    enc_1_period = micros() - enc_1_last;
    enc_1_last += enc_1_period;
}


void IRAM_ATTR ENC_2_ISR() 
{
    enc_2_period = micros() - enc_2_last;
    enc_2_last += enc_2_period;
}

void setup(){
    Serial.begin(9600);
    
    pinMode(ENC_2, INPUT_PULLUP);
    pinMode(ENC_1, INPUT_PULLUP);
    pinMode(OUT_PIN, OUTPUT);
    attachInterrupt(ENC_1, ENC_1_ISR, RISING);
    attachInterrupt(ENC_2, ENC_2_ISR, RISING);
    
    

}


void loop(){

    reg_e[reg_e_i] = enc_2_period - enc_1_period;
    reg_e_i++;
    if (reg_e_i == 8){
       reg_e_i = 0;
          reg_e_II[reg_e_i_II] = reg_e_av();
    reg_e_i_II++;
    if (reg_e_i_II == 8){
       reg_e_i_II = 0;
    } 
    }






    if(enc_1_period < 1500){
        digitalWrite(OUT_PIN, HIGH);
    }


        last_sp = micros() - l_sp;
    if (last_sp > 1000)
    {
        if (reg_e_av_II() < 1025)
        {
    Serial.println(reg_e_av_II()>>2);
        }
    l_sp = micros();
    last_sp = 0;
    }
   // delay(1);

    /*last_sp = micros() - l_sp;
    if (last_sp > 1000)
    {
    uint32_t harald = enc_2_period - enc_1_period;
    Serial.println(harald);
        
    l_sp = micros();
    last_sp = 0;
    }

int32_t harald = enc_2_period - enc_1_period;
    Serial.println(harald);
    delay(10);

}

uint32_t reg_e_av(){
    uint32_t reg_e_sum = 0;
    for(int i = 0; i < 8; i++)
    {
        reg_e_sum += reg_e[i];
    }
    return reg_e_sum >> 3;

}

uint32_t reg_e_av_II(){
    uint32_t reg_e_sum_II = 0;
    for(int i = 0; i < 8; i++)
    {
        reg_e_sum_II += reg_e_II[i];
    }
    return reg_e_sum_II >> 3;

}

*/