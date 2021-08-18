#include "Memory.h"

Memory::Memory()
{
  
}

Memory::Memory(const Memory &memory)
{
  Copy(this, &memory, sizeof(memory));
}

Memory::~Memory()
{

}

void *Memory::Copy(void *destination, const void *source, uint64_t length)
{
    int8_t *destinationCopy = (int8_t*)destination;
    const int8_t *sourceCopy = (int8_t*)source;

    while (length--)
    {
        *destinationCopy++ = *sourceCopy++;
    }

    return destination;
}

void *Memory::Set(void *destination, int32_t value, uint64_t length)
{
  uint8_t *destinationCopy = (uint8_t*)destination;

  while (length-- > 0)
  {
    *destinationCopy++ = value;
  }

  return destination;
}