#include <Arduino.h>

#include "halvoeAtSPIHost.hpp"

halvoeDVI::AtHost::SPILink dviSPILink;
elapsedMicros timeSinceLastFrame;
unsigned long frameInterval = 30 * 1000;//18000; // micro seconds
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
    dviSPILink.fillScreen(0);
    Serial.println("fillScreen() done");
    delay(1000);
    dviSPILink.fillRect(x, y, 25, 25, 255);
    Serial.println("fillRect() done");
    delay(1000);
    dviSPILink.swap();
    Serial.println("swap() done");
    delay(1000);

    ++x; if (x == 320 - 25) { x = 0; }
    timeSinceLastFrame = 0;
  }
}
