#pragma once
#include <core32.h>

namespace Core32
{
  class CGpio
  {
  public:
    CGpio(VPort port) : m_port(port)
    {
    }
    
    ~CGpio()
      {
      }
    
    void SetInput(uint32_t bits)
    {
      GPIO_SetInput(m_port, bits);
    }

    void SetOutput(uint32_t bits)
    {
      GPIO_SetOutput(m_port, bits);
    }

    void Set(uint32_t bits)
    {
      GPIO_SetBits(m_port, bits);
    }

    void Clear(uint32_t bits)
    {
      GPIO_ClearBits(m_port, bits);
    }

    void Toggle(uint32_t bits)
    {
      GPIO_ToggleBits(m_port, bits);
    }

    void Write(uint32_t bits)
    {
      GPIO_Write(m_port, bits);
    }

    uint32_t Read()
    {
      return GPIO_Read(m_port);
    }

  private:
    VPort m_port;
  };
}
