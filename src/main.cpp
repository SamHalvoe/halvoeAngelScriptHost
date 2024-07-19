#include <Arduino.h>

#include "halvoeAtSPIHost.hpp"

halvoeDVI::AtHost::SPILink dviSPILink;
GFXcanvas8 frame(320, 240);
uint16_t x = 0;
uint16_t y = 5;

void setup()
{
  Serial.begin(115200);
  while (not Serial) { delay(500); }
  Serial.println("Host Serial to USB is ready.");

  dviSPILink.begin();
  Serial.println("Host leaves setup.");
}

void loop()
{
  if (dviSPILink.isDVIReady())
  {
    frame.fillScreen(0);
    frame.fillRect(x, y, 25, 25, 255);
    ++x; if (x == 320 - 25) { x = 0; }

    Serial.println("dviSPILink.transferFrame(frame)");
    dviSPILink.transferFrame(frame);
    delay(40);
  }
}