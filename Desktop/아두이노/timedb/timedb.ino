#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include <NTPClient.h>
#include <WiFiUdp.h>



IPAddress serverAddr(192,168,0,47);
char user[] = "jungle";
char passwd[] = "1234";

const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
char sql[100];
char sdateTime[30];

WiFiClient client;
MySQL_Connection conn((Client*)&client);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org",9*3600,60000);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while(WiFi.status()!=WL_CONNECTED){
    Serial.println("."); delay(500);
  }
  Serial.print("Local IP address: "); Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.update();

  String date_time = timeClient.getFormattedDate();
  int index_date = date_time.indexOf("T");
  String date = date_time.substring(0, index_date); 
  date_time = date + " " +timeClient.getFormattedTime();
  date_time.toCharArray(sdateTime, 30);
  sprintf(sql, "insert into dbsensor.tbsensor (Date) values ('%s')",sdateTime);
  Serial.println(sql);

  if (conn.connect(serverAddr, 3306, user, passwd)){
    delay(1000);
  }else{
    Serial.println("Connection failed");
  }
  Serial.println("Recording data.");
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(sql);
  delete cur_mem;
}

void loop() {
  
}
