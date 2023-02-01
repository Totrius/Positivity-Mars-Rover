#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "creds.h"

#define RXp2 16
#define TXp2 17


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
  Serial.println(           SSID);
  Serial.println(           PASS);

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
    Serial2.println("10");
    delay(2500);
    Serial2.println("160");
    delay(2500);

    
}