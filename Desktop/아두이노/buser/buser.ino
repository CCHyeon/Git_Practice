#define BUZ 5

void setup() {
pinMode(BUZ,OUTPUT);
Serial.begin(9600);
}


void loop() {
  for(int i=20; i<4000; i=i+100){
    tone(BUZ, i, 500);
    Serial.print("Freq: ");
    Serial.println(i);
    delay(500);
  }
  delay(3000);
}
