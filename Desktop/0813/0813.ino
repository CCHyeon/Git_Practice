#include <LiquidCrystal.h>

#define STATE_0 0
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3

volatile int state = STATE_0;
int distance1, distance2, distance3;

const int SW3 = 2;
const int trig = 10;
const int echo = 11;

LiquidCrystal clcd(7,8,9,3,4,5,6);

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  clcd.begin(16,2);
  attachInterrupt(0,isr_sw, FALLING);

  Serial.begin(9600);
  clcd.clear();
  clcd.setCursor(0,0);
  clcd.print("PRESS button");
  clcd.setCursor(0,1);
  clcd.print("when you Ready!");
}

void loop() {}
  int cal_distance(){
    long echoTimeUs;
    double distanceMm;
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    echoTimeUs = pulseIn(echo, HIGH);
    distanceMm = echoTimeUs * (331.5+0.6*25.0) / 2.0/1000.0;

   return((ceil)(distanceMm));
  }

void display_clcd(int distanceMm){
  int quotient, reminder;
  quotient = distanceMm / 1000; reminder = distanceMm % 1000;
  clcd.write((char)quotient + '0');
  quotient = reminder / 100; reminder = reminder % 100;
  clcd.write((char)quotient + '0');
  quotient = reminder / 10; reminder = reminder % 10;
  clcd.write((char)quotient + '0');
  clcd.write((char)reminder+'0');
}

void isr_sw(){
  delay(100);
  if(digitalRead(SW3) == HIGH) return;
  switch(state){
    case STATE_0:
    clcd.clear(); clcd.setCursor(0,0); clcd.print("Ceiling Height"); clcd.setCursor(0,1);
    distance1=cal_distance(); display_clcd(distance1); clcd.print(" cm"); state=STATE_1;
    break;
    case STATE_1:
    clcd.clear(); clcd.setCursor(0,0); clcd.print("Ceiling Height"); clcd.setCursor(0,1);
    distance2=cal_distance(); display_clcd(distance2); clcd.print(" cm"); state=STATE_2;
    break;
    case STATE_2:
    clcd.clear(); clcd.setCursor(0,0); clcd.print("MY Height"); clcd.setCursor(0,1);
    distance3 = distance1- distance2; display_clcd(distance3); clcd.print(" cm"); state = STATE_3;
    break;

    case STATE_3:
    clcd.clear(); clcd.setCursor(0,0); clcd.print("PRESS button"); clcd.setCursor(0,1);
    clcd.print("when you READY!"); state = STATE_0;
    break;
}
}
