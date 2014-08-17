// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include "config.h"
#include "ardumidi.h"



#define LEDPIN     13     // status LED pin
int PIEZOTHRESHOLD[4] = { 5, 5, 5, 5 };  // analog threshold for piezo sensing
#define PADNUM 4          // number of pads

#define TOFF 0

int val;

int t[PADNUM];
uint32_t hold[PADNUM];

void analog_setup() {
  pinMode(LEDPIN, OUTPUT);
  
  for (int i=0;i<PADNUM;i++) {
    t[i]=0;  
    hold[i]=0;
  }
 // Serial.begin(57600);   // set serial output rate

}

uint32_t max1;

#define SAMPLES 70

int read_analog(int ch,uint32_t val) {

  int32_t avg=val;
  int32_t g;
  
  max1 = val;
  
  for (int i=0;i<(SAMPLES-1);i++) {
    
    g = (int32_t)analogRead(ch);
    avg += g;
    if (g > max1) max1 = g;
    
    //delayMicroseconds(1);
  }
  return avg / SAMPLES;

}

char gain[4]={13,15,45,15};
char velos[4];
char midi_notes[4]={49,47,46,38};

char hits=0;

void poll_adcs() {
  uint32_t r;
  
  
   // Loop through each piezo and send data
  // on the serial output if the force exceeds
  // the piezo threshold
  for(int i = 0; i < PADNUM; i++) {
    val = analogRead(i);
    r = millis();
    if(( val >= PIEZOTHRESHOLD[i] ) && (t[i]==0)) {
      
      
      
      val = read_analog(i,val);
      
      if ((val >= PIEZOTHRESHOLD[i]) && (max1 > 50)) {
        hits |= (1<<i);
        hold[i]=micros();
        t[i]=1;
        
        //Serial.println(hold[i]);
        
        max1 = gain[i]*max1;
        max1 = max1 / 100;
        
        if (max1 > 127) max1 = 127;
        if (max1 < 30) max1 = 30;
        
        velos[i]=max1;
        
        #ifndef MIDI
        digitalWrite(LEDPIN,HIGH);  // indicate we're sending MIDI data
        Serial.print(i);
        Serial.print(",");
        Serial.print((int)val);
        Serial.print(":");
        Serial.print((int)max1);
        Serial.println();
        digitalWrite(LEDPIN,LOW);
        #else
        
        //r = millis() - r;
        midi_note_on(0, midi_notes[i], velos[i]); 
        
        #endif
      }
      
      
    }

    if (hold[i])
      if ((micros()- hold[i]) > 20000 && val == 0) {
     // Serial.println(r);
        hold[i]=0;
        hits &= ~(1<<i);
        t[i]=0;
        #ifdef MIDI
        
        midi_note_off(0, midi_notes[i], velos[i]); 
      
      #endif
     }
  }
}
