#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "creds.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

#include "structures.h"

#define RXp2 23 
#define TXp2 22 
#define RXp1 21 
#define TXp1 19 

AsyncWebServer serwer(80);
struct datagram_servo mydata;
void toSend(char type, char id, char action){
  struct datagram_servo mydata;
  mydata.type = type;
  mydata.servo_id = id;
  mydata.servo_action = action;
  send_data(sizeof(mydata), (byte*) &mydata);
}
void sendToRover (char id){
  Serial1.write(id);
}
void setup() {
  esp_log_level_set("*", ESP_LOG_ERROR);        // set all components to ERROR level
  esp_log_level_set("wifi", ESP_LOG_WARN);      // enable WARN logs from WiFi stack
  esp_log_level_set("dhcpc", ESP_LOG_INFO);     // enable INFO logs from DHCP client


  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  Serial1.begin(9600, SERIAL_8N1, RXp1, TXp1);
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


  
  
//tutaj odbywa sie obsługa zapytań
serwer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ //na otrzymane od klienta zapytanie pod adresem "/" typu GET, 
  Serial.println("dostalem cos niecos");
  delay(500);
    request->send(SPIFFS, "/index.html", "text/html");           //odpowiedz mu kodem 200, danymi tekstowymi, o treści "Witaj! :)"
  });
serwer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send(SPIFFS, "/style.css", "text/css");
 });
serwer.on("/positivity.js", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(SPIFFS, "/positivity.js", "text/javascript");
});

serwer.on("/czZeroMinus", HTTP_GET, [](AsyncWebServerRequest *request){ 
  toSend(1, 0, 2);
  request->send(200, "text/plain", "");                                  
});
serwer.on("/czZeroPlus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 0, 1);
  request->send(200, "text/plain", "");                                 
});
serwer.on("/czJedenMinus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 1, 2);
  request->send(200, "text/plain", "");                                   
});
serwer.on("/czJedenPlus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 1, 1);
  request->send(200, "text/plain", "");                                  
});
serwer.on("/czDwaMinus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 2, 2);
  request->send(200, "text/plain", "");                                 
});
serwer.on("/czDwaPlus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 2, 1);
  request->send(200, "text/plain", "");                                
});
serwer.on("/czTrzyMinus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 3, 2);
  request->send(200, "text/plain", "");                                  
});
serwer.on("/czTrzyPlus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 3, 1);
  request->send(200, "text/plain", "");                                 
});
serwer.on("/czCzteryMinus", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 4, 2);
  request->send(200, "text/plain", "");                                    
});
serwer.on("/czCzteryPlus", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(1, 4, 1);  
  request->send(200, "text/plain", "");                                   
});
serwer.on("/klapkaPojemnikaGora", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(1, 5, 1);  
  request->send(200, "text/plain", "");                                   
});
serwer.on("/klapkaPojemnikaDol", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 5, 2);
  request->send(200, "text/plain", "");                                    
});
serwer.on("/pojemnikObrotPrawo", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(1, 6, 1);  
  request->send(200, "text/plain", "");                                   
});
serwer.on("/pojemnikObrotLewo", HTTP_GET, [](AsyncWebServerRequest *request){  
  toSend(1, 6, 2);
  request->send(200, "text/plain", "");                                    
});
serwer.on("/servoStop", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(1, 0, 3);  
  request->send(200, "text/plain", "");                                
});
serwer.on("/hClose", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(2, 0, 1);  
  request->send(200, "text/plain", "");                                
});
serwer.on("/hOpen", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(2, 0, 2);  
  request->send(200, "text/plain", "");                                
});
serwer.on("/hStop", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(2, 0, 3);  
  request->send(200, "text/plain", "");                                
});
serwer.on("/pomiary", HTTP_GET, [](AsyncWebServerRequest *request){
  toSend(3, 0, 0);  
  request->send(200, "text/plain", "");                                
});

// lazik:
serwer.on("/lazikPrzod", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(1);
  request->send(200, "text/plain", "");                                
});
serwer.on("/lazikTyl", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(2);
  request->send(200, "text/plain", "");                                
});
serwer.on("/lazikObrotLewo", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(3);
  request->send(200, "text/plain", "");                                
});
serwer.on("/lazikObrotPrawo", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(4);
  request->send(200, "text/plain", "");                                
});
serwer.on("/lazikStop", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(0);
  request->send(200, "text/plain", "");                                
});
// kamera
serwer.on("/kameraGora", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(8);
  request->send(200, "text/plain", "");                                
});
serwer.on("/kameraDol", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(9);
  request->send(200, "text/plain", "");                                
});
serwer.on("/kameraLewo", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(6);
  request->send(200, "text/plain", "");                                
});
serwer.on("/kameraPrawo", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(7);
  request->send(200, "text/plain", "");                                
});
serwer.on("/kameraStop", HTTP_GET, [](AsyncWebServerRequest *request){
  sendToRover(5);
  request->send(200, "text/plain", "");                                
});


 serwer.begin();
}

void loop() {
  if (Serial2.available())
  {
    Serial.println(Serial2.read());
  }
}

// #include <sstream>

// serwer.on("/getSensorData", HTTP_GET, [](AsyncWebServerRequest *request) {
  
//   int odczyt = 3; ///odczytaj dane z czujnika

//   std::stringstream ss;
//   ss << "{'success': true, sensordata: " << odczyt << "}";
   
//   /*
//     fetch("/getSensorData")
//       .then(response => response.json())
//       .then(data => console.log(data.sensordata)) // -> wyświetli 3
//   */

//   request->send(200, "text/plain", ss.str().c_str());
// });