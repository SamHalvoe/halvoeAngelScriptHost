#pragma once

#include <array>
#include <Adafruit_GFX.h>
#include "halvoeSPIPicoDVI.hpp"

namespace halvoeDVI::AtHost
{
#ifdef ARDUINO_ARCH_RP2040
  #error Currently not implemented!
#elif __IMXRT1062__
  const uint8_t IS_DVI_READY_PIN = 30;
  const uint8_t CS_PIN = 0;

  class SPILink
  {
    private:
      HALVOE_SPI_CLASS& m_spiInterface;
      SPISettings m_spiSettings;
      std::array<uint8_t, COMMAND_BUFFER_SIZE> m_commandBuffer;
      uint16_t m_commandSize = 0;

    private:
      void transferCommand()
      {
        m_spiInterface.beginTransaction(m_spiSettings);
        digitalWriteFast(CS_PIN, LOW);
        m_spiInterface.transfer(m_commandBuffer.data(), nullptr, m_commandSize);
        digitalWriteFast(CS_PIN, HIGH);
        m_spiInterface.endTransaction();
      }

    public:
      SPILink(HALVOE_SPI_CLASS& io_spiInterface = HALVOE_SPI_DEFAULT) : m_spiInterface(io_spiInterface)
      {}

      void begin(const SPISettings& in_spiSettings = SPI_DEFAULT_SETTINGS)
      {
        pinMode(IS_DVI_READY_PIN, INPUT);
        pinMode(CS_PIN, OUTPUT);
        digitalWriteFast(CS_PIN, HIGH);
        m_spiSettings = in_spiSettings;
        m_spiInterface.begin();
      }

      bool isDVIReady() const
      {
        return digitalReadFast(IS_DVI_READY_PIN) == HIGH;
      }
      
      void swap()
      {
        m_commandSize = 4;
        *reinterpret_cast<uint16_t*>(m_commandBuffer.data()) = m_commandSize - 2;
        *(reinterpret_cast<uint16_t*>(m_commandBuffer.data()) + 1) = fromGFXCommand(GFXCommand::swap);
        transferCommand();
      }

      void fillScreen(uint16_t in_color)
      {
        m_commandSize = 6;
        *reinterpret_cast<uint16_t*>(m_commandBuffer.data()) = m_commandSize - 2;
        *(reinterpret_cast<uint16_t*>(m_commandBuffer.data()) + 1) = fromGFXCommand(GFXCommand::fillScreen);
        *(reinterpret_cast<uint16_t*>(m_commandBuffer.data()) + 2) = in_color;
        transferCommand();
      }

      void fillRect(int16_t in_x, int16_t in_y, int16_t in_width, int16_t in_height, uint16_t in_color)
      {
        m_commandSize = 14;
        *reinterpret_cast<uint16_t*>(m_commandBuffer.data()) = m_commandSize - 2;
        *(reinterpret_cast<uint16_t*>(m_commandBuffer.data()) + 1) = fromGFXCommand(GFXCommand::fillRect);
        *(reinterpret_cast<int16_t*>(m_commandBuffer.data()) + 2) = in_x;
        *(reinterpret_cast<int16_t*>(m_commandBuffer.data()) + 3) = in_y;
        *(reinterpret_cast<int16_t*>(m_commandBuffer.data()) + 4) = in_width;
        *(reinterpret_cast<int16_t*>(m_commandBuffer.data()) + 5) = in_height;
        *(reinterpret_cast<uint16_t*>(m_commandBuffer.data()) + 6) = in_color;
        transferCommand();
      }
  };
#else
  #error Unsupported MCU!
#endif
}
