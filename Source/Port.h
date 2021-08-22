/*+===================================================================
  File:      Port.h

  Summary:   Classes for hardware communication with ports.

  Classes:   Port, Port8, Port8Slow, Port16, Port32.

  Copyright and Legal notices.
===================================================================+*/

#ifndef _PORT_H
#define _PORT_H

#include "Types.h"
#include "Memory.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Port

  Summary:  Basic communication with ports.

  Methods:  Port
              Default/Copy constructor.
            Port
              Constructor which initialize the port number.
            ~Port
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Port
{
protected:
    Port();
    Port(const Port &port);
    Port(uint16_t portNumber);
    ~Port();

    uint16_t m_portNumber;
};

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Port8

  Summary:  Basic communication with ports.

  Methods:  Write
              Writes data to a port.
            Read
              Reads data from a port.
  
            Port8
              Default/Copy constructor.
            Port8
              Constructor which initialize the port number.
            ~Port8
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Port8: public Port
{
public:
    Port8();
    Port8(const Port8 &port8);
    Port8(uint16_t portNumber);
    ~Port8();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port8::Write

      Summary:  Writes data to a port.

      Args:     uint8_t data
                  The data to be written to the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual void Write(uint8_t data);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port8::Read

      Summary:  Reads data from a port.

      Returns:  uint8_t
                The data retrieved from the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual uint8_t Read();
};

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Port8Slow

  Summary:  Basic communication with ports.

  Methods:  Write
              Writes data to a port.
  
            Port8Slow
              Default/Copy constructor.
            Port8Slow
              Constructor which initialize the port number.
            ~Port8Slow
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Port8Slow: public Port8
{
public:
    Port8Slow();
    Port8Slow(const Port8Slow &port8Slow);
    Port8Slow(uint16_t portNumber);
    ~Port8Slow();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port8Slow::Write

      Summary:  Writes data to a port.

      Args:     uint8_t data
                  The data to be written to the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual void Write(uint8_t data);
};

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Port16

  Summary:  Basic communication with ports.

  Methods:  Write
              Writes data to a port.
            Read
              Reads data from a port.
  
            Port16
              Default/Copy constructor.
            Port16
              Constructor which initialize the port number.
            ~Port16
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Port16: public Port
{
public:
    Port16();
    Port16(const Port16 &port16);
    Port16(uint16_t portNumber);
    ~Port16();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port16::Write

      Summary:  Writes data to a port.

      Args:     uint16_t data
                  The data to be written to the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual void Write(uint16_t data);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port16::Read

      Summary:  Reads data from a port.

      Returns:  uint16_t
                The data retrieved from the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual uint16_t Read();
};

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Port32

  Summary:  Basic communication with ports.

  Methods:  Write
              Writes data to a port.
            Read
              Reads data from a port.
  
            Port32
              Default/Copy constructor.
            Port32
              Constructor which initialize the port number.
            ~Port32
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Port32: public Port
{
public:
    Port32();
    Port32(const Port32 &port32);
    Port32(uint16_t portNumber);
    ~Port32();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port32::Write

      Summary:  Writes data to a port.

      Args:     uint32_t data
                  The data to be written to the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual void Write(uint32_t data);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Port32::Read

      Summary:  Reads data from a port.

      Returns:  uint32_t
                The data retrieved from the port.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    virtual uint32_t Read();
};

#endif // !_PORT_H