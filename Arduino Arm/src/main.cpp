#include <Arduino.h>
#include <Servo.h>
#include "Stepper.h"

#define TYPE_SERVO_POSITION 1
#define LEN_SERVO_POSITION 3

Stepper mojSilnik(2048, 43, 47, 45, 49); // 32*64=2048
Servo servoCzlon0;
Servo servoCzlon1;
Servo servoCzlon2;
Servo servoCzlon3;
Servo servoCzlon4;
Servo servoPojKlapka;
Servo servoPojObrot;
int pozycjeServRamienia[] = {86, 10, 0, 180, 90, 90, 90}; // cz0, cz1, cz2, cz3, cz4, pojemnikKlapka, pojemnikObrot

int idServa;
int inkrement;
int kroki;
bool ruchServa;
bool ruchLyzki;



struct datagram_servo {
  byte type = 1; // id pakietu
  byte servo_id; // id serwa (0-255)
  byte servo_action; // pozycja serwa (0-255)
};

struct datagram_servo read_datagram_servo() {
  struct datagram_servo data;
  
  data.type = Serial.read();
  data.servo_id = Serial.read();
  data.servo_action = Serial.read();

  return data;
}



void odczyt() {
    struct datagram_servo data = read_datagram_servo();

    switch(data.type){ // type
      case 1: {
        //to jest serwo:
        idServa = data.servo_id;
        //Serial.println(idServa);
          switch(data.servo_action){
            case 1: {
              //zwiekszanie
              inkrement = 1;
              ruchServa = true;
              break;
            } 
            case 2: {
              // zmniejszanie
              inkrement = -1;
              ruchServa = true;
              break;
            } 
            case 3: {
              // stop
              ruchServa = false;
              break;
            } 
          }
       
      break;
      }
      case 2: {
        //to jest silnik krokowy 
        switch (data.servo_action)
        {
          case 1: {
            //zamykanie
            kroki = 256;
            ruchLyzki = true;
            break;
          }
          case 2: {
            //otwieranie
            kroki = -256;
            ruchLyzki = true;
            break;
          }
          case 3:{
            // stop ruchu
            ruchLyzki = false;
            break;
          }       
        
        }
        break;       
      }
     
      case 3: {
        //prosba o pomiary
        makeMeasurements();
        break;
      }
    }
}
void makeMeasurements() {

}
void moveManipulator (int id, int ink){
  pozycjeServRamienia[id] = pozycjeServRamienia[id]+ ink;
  if (pozycjeServRamienia[id] >=180){
    pozycjeServRamienia[id]=180;
  }
  if (pozycjeServRamienia[id] <=0) {
    pozycjeServRamienia[id] = 0;
  }

  switch(id){
    case 0:{
      servoCzlon0.write(pozycjeServRamienia[id]);
      break;
    }
    case 1:{
      servoCzlon1.write(pozycjeServRamienia[id]);
      break;
    }
    case 2:{
      servoCzlon2.write(pozycjeServRamienia[id]);
      break;
    }
    case 3:{
      servoCzlon3.write(pozycjeServRamienia[id]);
      break;
    }
    case 4:{
      servoCzlon4.write(pozycjeServRamienia[id]);
      break;
    }
    case 5:{
      servoPojKlapka.write(pozycjeServRamienia[id]);
      break;
    }
    case 6:{
      servoPojObrot.write(pozycjeServRamienia[id]);
      break;
    }
  }
}

void setup() {
  Serial.begin(9600);
  servoCzlon0.attach(2);
  servoCzlon0.write(pozycjeServRamienia[0]);
  servoCzlon1.attach(3);
  servoCzlon1.write(pozycjeServRamienia[1]);
  servoCzlon2.attach(4);
  servoCzlon2.write(pozycjeServRamienia[2]);
  servoCzlon3.attach(5);
  servoCzlon3.write(pozycjeServRamienia[3]);
  servoCzlon4.attach(6);
  servoCzlon4.write(pozycjeServRamienia[4]);
  servoPojKlapka.attach(7);
  servoPojKlapka.write(pozycjeServRamienia[5]);
  servoPojObrot.attach(8);
  servoPojObrot.write(pozycjeServRamienia[6]);
  mojSilnik.setSpeed(10);
  ruchServa = false;
  ruchLyzki = false;
}

void loop() {
  if (Serial.available())
  {
    odczyt();
  }
  if (ruchServa){
    moveManipulator(idServa, inkrement);
    Serial.println(pozycjeServRamienia[idServa]);    
  }
  if (ruchLyzki){
    Serial.println("ruszam lyzka");
    mojSilnik.step(kroki);
  }
  
  delay(100);  
}