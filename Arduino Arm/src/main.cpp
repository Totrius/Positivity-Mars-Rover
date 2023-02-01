#include <Arduino.h>
//#include <Servo.h>

// Servo serwomechanizm;
int pozycja = 90;
String pozycjaStr;

void setup() {
  Serial.begin(9600);
  // serwomechanizm.attach(9);
  // serwomechanizm.write(90);
}
void loop() {
  if (Serial.available())
  {
   Serial.println(Serial.readString());
    pozycjaStr = Serial.readString();
    pozycja = Serial.parseInt();
    //serwomechanizm.write(pozycja);
    Serial.println(pozycjaStr);
    Serial.println(pozycja);
 }
  
}