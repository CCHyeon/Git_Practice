#define trig 8
#define echo 9

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  
 
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  
  
  duration = pulseIn(echo, HIGH);
  distance = duration * 170 / 1000;

  if (distance <100){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  
  Serial.print("거리: ");
  Serial.print(distance);
  Serial.println("mm");
  delay(100);
}
