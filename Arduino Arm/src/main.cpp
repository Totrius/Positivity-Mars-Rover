#include <Arduino.h>
#include <Servo.h>

#define TYPE_SERVO_POSITION 1
#define LEN_SERVO_POSITION 3

Servo serwomechanizm;
int pozycja = 90;
String pozycjaStr;

struct datagram_servo {
  byte type = 1; // id pakietu
  byte servo_id; // id serwa (0-255)
  byte servo_position; // pozycja serwa (0-255)
};

struct datagram_servo read_datagram_servo() {
  struct datagram_servo data;
  
  data.type = Serial.read();
  data.servo_id = Serial.read();
  data.servo_position = Serial.read();

  return data;
}

void setup() {
  Serial.begin(9600);
  serwomechanizm.attach(9);
  serwomechanizm.write(90);
}
void loop() {
  if (Serial.available())
  {
    struct datagram_servo data = read_datagram_servo();

    Serial.println("W buforze jest: ");
    Serial.print(data.type, DEC);
    Serial.print(' ');
    Serial.print(data.servo_id, DEC);
    Serial.print(' ');
    Serial.println(data.servo_position, DEC);
    Serial.println();

    serwomechanizm.write(data.servo_position);
  }
    delay(100);  
}