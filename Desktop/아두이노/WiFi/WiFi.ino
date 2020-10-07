//#include <WiFi.h>         //WIFI shield
#include <ESP8266WiFi.h>  //ESP8266
#include <PubSubClient.h>

#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
const char* nodeName = "Factory-A-0";

char* topic = "temp";
char* server = "192.168.0.47";

WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);
char data[10];

void setup() {
  Serial.begin(9600);

  dht.begin();

  WiFi.begin(ssid, password);
  while(WiFi.status() !=WL_CONNECTED){
    Serial.print("."); delay(500);
  }
  Serial.println("\nWiFi Connected");

  while (!client.connect(nodeName)){
    Serial.print("*"); delay(1000);
  }
  Serial.println("\nConnected to broker");
}
void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float temperature = dht.readTemperature();

  if(isnan(h)||isnan(temperature)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temp: ");
  Serial.println(temperature);
  
  String Str = String(temperature);
  Str.toCharArray(data, Str.length());
  client.publish(topic, data);
}
