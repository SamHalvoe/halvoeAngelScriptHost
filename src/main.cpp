#include <Arduino.h>

#include "halvoeAtSPIHost.hpp"

halvoeDVI::AtHost::SPILink dviSPILink;
GFXcanvas8 frame(320, 240);
uint8_t testValueSent = 42;
uint8_t testValueReceive = 127;

void setup()
{
  Serial.begin(115200);
  while (not Serial) { delay(500); }
  Serial.println("Host Serial to USB is ready.");

  dviSPILink.begin();
  frame.fillScreen(0xFFFF);
  Serial.println("Host leaves setup.");

  //pinMode(halvoeDVI::CS_PIN, OUTPUT);
}

void loop()
{
  /*HALVOE_SPI_DEFAULT.beginTransaction(halvoeDVI::SPI_DEFAULT_SETTINGS);
  digitalWrite(halvoeDVI::CS_PIN, LOW);
  testValueReceive = HALVOE_SPI_DEFAULT.transfer(testValueSent);
  digitalWrite(halvoeDVI::CS_PIN, HIGH);
  HALVOE_SPI_DEFAULT.endTransaction();
  Serial.println(testValueReceive);*/
  dviSPILink.transferFrame(frame);
  delay(5000);
}