#include <CapacitiveSensor.h>
#include <Servo.h>
#include "pitches.h"
#define NUM_OF_NOTES 28

Servo myservo;  // create servo object to control a servo
int pos = 0;
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
int SPEAKER = 8;

int   NOTE_SEQ[NUM_OF_NOTES] = {
      NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5, PAUSE,
      NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_G5, NOTE_F5, PAUSE,
      NOTE_C5, NOTE_C5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5, NOTE_D5, PAUSE,
      NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_F5 };
int   NOTE_LEN[NUM_OF_NOTES]   = {
      4,2,8,8,8,16,   50,     //50  millis for the first pause
      4,2,8,8,8,16,   100,    //100 millis for the second pause
      4,2,8,8,8,8,16, 150,    //150 millis for the third pause
      4,2,8,8,8,20 };

int   TEMPO = 65;

void playNote(int pitch,int duration) {
    tone( SPEAKER, pitch);
    delay( duration);
    noTone( SPEAKER);
}            
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
}

void loop() {
    long touchSensor =  cs_4_2.capacitiveSensor(30);
          Serial.println(touchSensor);

    if (touchSensor > 5000)  //touched
    {
      Serial.println(touchSensor);
      for (pos = 0; pos <= 90; pos += 1)
      { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(10);                       // waits 15ms for the servo to reach the position
      }
      for (int i = 0; i < NUM_OF_NOTES; i++) {
        if ( NOTE_SEQ[i] != PAUSE) {
            playNote( NOTE_SEQ[i], NOTE_LEN[i] * TEMPO);
      // delay after note reproduction following TEMPO variable's diktat
            delay( TEMPO);
        } else {
            // delay if this is a pause. (it will be in millis, check NOTE_LEN)
            delay( NOTE_LEN[i]);
        }
    }
      delay(2000);
      for (pos = 90; pos >= 0; pos -= 1)
      { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 15ms for the servo to reach the position
      }
      myservo.write(0);
    }
}
