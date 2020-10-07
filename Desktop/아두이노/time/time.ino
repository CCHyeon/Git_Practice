#include <NTPClient.h>
#include <ESP8266WiFi.h>
//#include <WiFi.h>
//#include <WiFi101.h>
#include <WiFiUdp.h>

const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 9*3600, 60000);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
}

void loop(){
  timeClient.update();
  String date_time = timeClient.getFormattedDate();
  int index_date = date_time.indexOf("T");

  String date = date_time.substring(0, index_date);

  date_time = date + " " +timeClient.getFormattedTime();
  Serial.println(date_time);

  delay(1000);
}
