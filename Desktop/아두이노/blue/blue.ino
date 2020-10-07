#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() {
  if (Serial.available()) {
    String str = Serial.readString();
    mySerial.println(str);
    Serial.println(str);
  }
  if (mySerial.available()) {
    String str = mySerial.readString();
    Serial.println(str);
  }
}
