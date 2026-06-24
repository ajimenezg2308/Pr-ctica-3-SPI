#include <SPI.h>

#define CS1 9
#define CS2 8
#define CS3 7
#define LED 6  // LED del master

void setup() {
  Serial.begin(9600);
  SPI.begin();
  
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);
  pinMode(CS3, OUTPUT);
  pinMode(LED, OUTPUT);
  
  digitalWrite(CS1, HIGH);
  digitalWrite(CS2, HIGH);
  digitalWrite(CS3, HIGH);
}

byte transferToSlave(int csPin, byte data) {
  digitalWrite(LED, HIGH);
  
  digitalWrite(csPin, LOW);
  delayMicroseconds(10);
  byte response = SPI.transfer(data);
  delayMicroseconds(10);
  digitalWrite(csPin, HIGH);
  
  digitalWrite(LED, LOW);
  delay(10);
  return response;
}

void loop() {
  byte r1 = transferToSlave(CS1, 0x01);
  Serial.print("Esclavo 1: 0x"); Serial.println(r1, HEX);
  delay(800);

  byte r2 = transferToSlave(CS2, 0x02);
  Serial.print("Esclavo 2: 0x"); Serial.println(r2, HEX);
  delay(800);

  byte r3 = transferToSlave(CS3, 0x03);
  Serial.print("Esclavo 3: 0x"); Serial.println(r3, HEX);
  delay(800);

  Serial.println("---");
  delay(1000);
}