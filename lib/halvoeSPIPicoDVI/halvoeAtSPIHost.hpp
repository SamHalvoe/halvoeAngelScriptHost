#pragma once

#include <Adafruit_GFX.h>
#include "halvoeSPIPicoDVI.hpp"

namespace halvoeDVI::AtHost
{
#ifdef ARDUINO_ARCH_RP2040
  #error Currently not implemented!
#elif __IMXRT1062__
  class SPILink
  {
    private:
      HALVOE_SPI_CLASS& m_spiInterface;
      SPISettings m_spiSettings;

    public:
      SPILink(HALVOE_SPI_CLASS& io_spiInterface = HALVOE_SPI_DEFAULT) : m_spiInterface(io_spiInterface)
      {}

      void begin(const SPISettings& in_spiSettings = SPI_DEFAULT_SETTINGS)
      {
        pinMode(CS_PIN, OUTPUT);
        m_spiSettings = in_spiSettings;
        m_spiInterface.begin();
      }
      
      void transferFrame(const GFXcanvas8& in_frame)
      {
        m_spiInterface.beginTransaction(m_spiSettings);
        digitalWrite(CS_PIN, LOW);
        m_spiInterface.transfer(in_frame.getBuffer(), FRAME_SIZE);
        digitalWrite(CS_PIN, HIGH);
        m_spiInterface.endTransaction();
      }
  };
#else
  #error Unsupported MCU!
#endif
}
