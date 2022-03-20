#ifndef _PORT_H
#define _PORT_H

#include <Common/Memory.h>
#include <Common/Types.h>

#define outb(port, value) outportb(port, value)
#define inb(value) inportb(value)

void outportb(uint16_t Port, uint8_t Value);
uint8_t inportb(uint16_t Port);

class Port
{
protected:
  Port();
  Port(const Port &port);
  Port(uint16_t portNumber);
  ~Port();

  uint16_t m_portNumber;
};

class Port8 : public Port
{
public:
  Port8();
  Port8(const Port8 &port8);
  Port8(uint16_t portNumber);
  ~Port8();

  virtual void Write(uint8_t data);
  virtual uint8_t Read();
};

class Port8Slow : public Port8
{
public:
  Port8Slow();
  Port8Slow(const Port8Slow &port8Slow);
  Port8Slow(uint16_t portNumber);
  ~Port8Slow();

  virtual void Write(uint8_t data);
};

class Port16 : public Port
{
public:
  Port16();
  Port16(const Port16 &port16);
  Port16(uint16_t portNumber);
  ~Port16();

  virtual void Write(uint16_t data);
  virtual uint16_t Read();
};

class Port32 : public Port
{
public:
  Port32();
  Port32(const Port32 &port32);
  Port32(uint16_t portNumber);
  ~Port32();

  virtual void Write(uint32_t data);
  virtual uint32_t Read();
};

#endif // !_PORT_H