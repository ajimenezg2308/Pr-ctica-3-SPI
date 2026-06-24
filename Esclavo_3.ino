#include <SPI.h>

#define LED 6

volatile byte received;
volatile bool dataReady = false;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  pinMode(LED, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

ISR(SPI_STC_vect) {
  received = SPDR;
  SPDR = 0xA3;
  dataReady = true;
}

void loop() {
  if (dataReady) {
    for(int i = 0; i < 3; i++) {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
    }
    Serial.print("Slave 3 recibio: 0x");
    Serial.println(received, HEX);
    dataReady = false;
  }
}
