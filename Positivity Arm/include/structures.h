#include <Arduino.h>

struct datagram_servo {
  byte type = 1; // id pakietu
  byte servo_id; // id serwa (0-255)
  byte servo_position; // pozycja serwa (0-255)
};

void send_data(byte length, byte* data) {
  for(byte i = 0; i < length; ++i){
    uint8_t m = data[i];
    Serial2.write(m);
  }
}
