#include <Arduino.h>

#include "halvoeAtSPIHost.hpp"

#include <cstring>

halvoeDVI::AtHost::SPILink dviSPILink;
elapsedMicros timeSinceLastFrame;
unsigned long frameInterval = 18000; // micro seconds
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
  timeSinceLastFrame = frameInterval;
}

void loop()
{
  if (dviSPILink.isDVIReady() && timeSinceLastFrame >= frameInterval)
  {
    frame.fillScreen(0);
    frame.fillRect(x, y, 25, 25, 255);
    ++x; if (x == 320 - 25) { x = 0; }

    dviSPILink.transferFrame(frame);
    Serial.println("dviSPILink.transferFrame(frame) done");
    timeSinceLastFrame = 0;
  }
}
