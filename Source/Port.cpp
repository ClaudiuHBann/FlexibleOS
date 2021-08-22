#include "Port.h"

Port::Port()
{

}

Port::Port(const Port &port)
{
    Memory::Copy(this, &port, sizeof(port));
}

Port::Port(uint16_t portNumber)
{
    m_portNumber = portNumber;
}

Port::~Port()
{

}

Port8::Port8()
{

}

Port8::Port8(const Port8 &port8)
{
    Memory::Copy(this, &port8, sizeof(port8));
}

Port8::Port8(uint16_t portNumber):
Port(portNumber)
{

}

Port8::~Port8()
{

}

void Port8::Write(uint8_t data)
{
    __asm__ volatile("outb %0, %1": :"a" (data), "Nd" (m_portNumber));
}

uint8_t Port8::Read()
{
    uint8_t result;

    __asm__ volatile("inb %1, %0": "=a" (result) : "Nd" (m_portNumber));

    return result;
}

Port8Slow::Port8Slow()
{

}

Port8Slow::Port8Slow(const Port8Slow &port8Slow)
{
    Memory::Copy(this, &port8Slow, sizeof(port8Slow));
}

Port8Slow::Port8Slow(uint16_t portNumber):
Port8(portNumber)
{

}

Port8Slow::~Port8Slow()
{

}

void Port8Slow::Write(uint8_t data)
{
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:": :"a" (data), "Nd" (m_portNumber));
}

Port16::Port16()
{

}

Port16::Port16(const Port16 &port16)
{
    Memory::Copy(this, &port16, sizeof(port16));
}

Port16::Port16(uint16_t portNumber):
Port(portNumber)
{

}

Port16::~Port16()
{

}

void Port16::Write(uint16_t data)
{
    __asm__ volatile("outw %0, %1": :"a" (data), "Nd" (m_portNumber));
}

uint16_t Port16::Read()
{
    uint16_t result;

    __asm__ volatile("inw %1, %0": "=a" (result) : "Nd" (m_portNumber));

    return result;
}

Port32::Port32()
{

}

Port32::Port32(const Port32 &port32)
{
    Memory::Copy(this, &port32, sizeof(port32));
}

Port32::Port32(uint16_t portNumber):
Port(portNumber)
{

}

Port32::~Port32()
{

}

void Port32::Write(uint32_t data)
{
    __asm__ volatile("outl %0, %1": :"a" (data), "Nd" (m_portNumber));
}

uint32_t Port32::Read()
{
    uint32_t result;

    __asm__ volatile("inl %1, %0": "=a" (result) : "Nd" (m_portNumber));

    return result;
}