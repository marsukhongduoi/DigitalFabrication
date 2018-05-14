#include <CapacitiveSensor.h>
#include <Servo.h>
#include "pitches.h"
#define NUM_OF_NOTES 28

Servo myservo;  // create servo object to control a servo
int pos = 0;
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
int buzzer_pin = 8;

struct MusicStruct {
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
}Music;

struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
}Length;

int tempo = 400;

void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}         
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(60);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
}

void loop() {
    long touchSensor =  cs_4_2.capacitiveSensor(30);
          Serial.println(touchSensor);

    if (touchSensor > 2000)  //touched
    {
      Serial.println(touchSensor);
      for (pos = 60; pos >= 0; pos -= 1)
      { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 15ms for the servo to reach the position
      }
        setTone(buzzer_pin, Music.B, tempo * Length.one);
        setTone(buzzer_pin, Music.E, tempo * Length.one_half);
        setTone(buzzer_pin, Music.G, tempo * Length.half);
        setTone(buzzer_pin, Music.F, tempo * Length.one);
        setTone(buzzer_pin, Music.E, tempo * Length.two);
        setTone(buzzer_pin, Music.B2, tempo * Length.one);
        setTone(buzzer_pin, Music.A2, tempo * Length.two_half);
        setTone(buzzer_pin, Music.Fs, tempo * Length.two_half);
        
        setTone(buzzer_pin, Music.E, tempo * Length.one_half);
        setTone(buzzer_pin, Music.G, tempo * Length.half);
        setTone(buzzer_pin, Music.F, tempo * Length.one);
        setTone(buzzer_pin, Music.Ds, tempo * Length.two);
        setTone(buzzer_pin, Music.F, tempo * Length.one);
        setTone(buzzer_pin, Music.B, tempo * Length.two_half);
      delay(2000);
      for (pos = 0; pos <= 60; pos += 1)
      { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(50);                       // waits 15ms for the servo to reach the position
      }
    }
    delay(100);
}
