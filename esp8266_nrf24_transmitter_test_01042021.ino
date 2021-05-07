#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(2, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

void loop() {
  const char text[] = "Hello Tobie 1 2 3 4 5 6 7 8 9 10";
  radio.write(&text, sizeof(text));

  delay(1 );
}
