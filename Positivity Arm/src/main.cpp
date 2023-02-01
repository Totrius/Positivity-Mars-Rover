#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "creds.h"

#include "structures.h"

#define RXp2 23
#define TXp2 22


AsyncWebServer serwer(80);

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.printf("\nAdres IP: ");
  Serial.println(WiFi.localIP());
  
  delay(2000);
  
  
//tutaj odbywa sie obsługa zapytań
serwer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ //na otrzymane od klienta zapytanie pod adresem "/" typu GET, 
  Serial.println("dostalem cos niecos");
  delay(500);
    request->send(SPIFFS, "/index.html", "text/html");           //odpowiedz mu kodem 200, danymi tekstowymi, o treści "Witaj! :)"
  });
  serwer.begin();
}
void loop() {
  struct datagram_servo mydata;
  mydata.servo_id = 1;
  mydata.type = 1;
  mydata.servo_position = 0;
  send_data(sizeof(mydata), (byte*) &mydata);

  delay(2500);

  mydata.servo_id = 1;
  mydata.type = 1;
  mydata.servo_position = 180;
  send_data(sizeof(mydata), (byte*) &mydata);

  delay(2500);    
}