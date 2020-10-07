#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "DHT.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

#define DHTPIN D4
#define DHTTYPE DHT11

IPAddress serverAddr(192,168,0,47);
char user[] = "jungle";

char passwd[] = "1234";

const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
char sql[150];
char sdateTime[30];

WiFiClient client;
MySQL_Connection conn((Client*)&client);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org",9*3600,60000);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while(WiFi.status()!=WL_CONNECTED){
    Serial.println("WiFi Connecting...");
    delay(500);
  }
  Serial.print("Local IP address: "); Serial.println(WiFi.localIP());
}

void loop() {
  timeClient.begin();
  timeClient.update();

  String date_time = timeClient.getFormattedDate();
  int index_date = date_time.indexOf("T");
  String date = date_time.substring(0, index_date); 
  date_time = date + " " +timeClient.getFormattedTime();
  date_time.toCharArray(sdateTime, 30);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Date : "); Serial.println(sdateTime);
  Serial.print("H : "); Serial.println(h);
  Serial.print("T : "); Serial.println(t);

  sprintf(sql, "insert into dbsensor.tbsensor (Date, Humidity, Temperature) values ('%s', '%f', '%f')",sdateTime, h, t);

   if (conn.connect(serverAddr, 3306, user, passwd)){
    Serial.println("Connected!!!!");
    delay(200);
  }else{
    Serial.println("Connection failed");
  }

  Serial.println("Recording data.");
  Serial.println(sql);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(sql);
  delete cur_mem;
  delay(20000);
  
}
