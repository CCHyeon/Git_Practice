int ledPinA=13;
int ledPinB=11;

int ledStateA=LOW;
int ledStateB=LOW;
long prevTime13 = 0;
long prevTime11 = 0;
long interval13 = 1000;
long interval11 = 500;

void setup() {
  pinMode(ledPinA,OUTPUT);
  pinMode(ledPinB,OUTPUT);
}


void loop() 
{
  unsigned long int currentTime = millis();

  if(currentTime - prevTime13 > interval13){
    prevTime13 = currentTime;
    ledStateA = !ledStateA;
    digitalWrite(ledPinA, ledStateA);
  }
  
  if(currentTime - prevTime11 > interval11){
    prevTime11 = currentTime;
    ledStateB = !ledStateB;
    digitalWrite(ledPinB, ledStateB);
  }
}
