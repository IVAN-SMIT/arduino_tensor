#include "GyverHX711.h"
GyverHX711 sensor(0, 8, HX_GAIN64_A); //аналоговые пины

#define PIN_POT     A0 //потенциометр

float calibration_factor = -3.7; // калибровка датчика
float e = 0;

int rele1 = 30; //ардуино цифровые пины
int rele2 = 28;

int tensor = 48;

void setup() {
  Serial.begin(9600);
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(PIN_POT, INPUT);
  pinMode(tensor, OUTPUT);
  sensor.tare();// сбрасываем датчик на 0
  sensor.sleepMode(false) ;
  pinMode(49, OUTPUT);

}
void close_rele(int pin){
  digitalWrite(pin, HIGH);
}
void open_rele(int pin){
  digitalWrite(pin, LOW);
}
void PID(int pin, int t){
 open_rele(pin);
 delay(t);
 close_rele(pin);
 delay(t);
}

void push(int pin, int t, int count){
  int i = 0;
  while(i< count){
    PID(pin, t);
    i++;
  }
}

void rele_reg(int power, int rele){
switch (power) {

    case 0:
      break;

    case 1:
      //
      Serial.print("push push slower");
      push(rele, 70, 2);
      break;

    case 2:
      //
      Serial.print("push push faster");
      push(rele, 50, 2);
      break;

     case 3:
      //
      Serial.print("push push very low");
      push(rele, 100, 2);
      break;

    case 20:
      //
      Serial.print("opening ");
      open_rele(rele);
      break;

    case 30:
      //
      Serial.print("closing ");
      close_rele(rele);
      break;

    default:
      Serial.println("\n 1 2 or 3");
  }
}


void loop() {
  int rotat;
    rotat = analogRead(PIN_POT);
    Serial.print(rotat);
    Serial.print("\n");

    while (Serial.available() == 0) {}

  int power = Serial.parseInt();
  rele_reg(power, rele1);
  rele_reg(power, rele2);

  open_rele(rele1);
  open_rele(rele2);
  delay(500);
  close_rele(rele1);
  close_rele(rele2);
  delay(500);


}
