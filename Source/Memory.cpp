#include "Memory.h"

Memory::Memory()
{
  
}

Memory::Memory(const Memory &memory)
{
  MemoryCopy(this, &memory, sizeof(memory));
}

Memory::~Memory()
{

}

void *Memory::MemoryCopy(void *destination, const void *source, uint64_t length)
{
    int8_t *d = (int8_t*)destination;
    const int8_t *s = (int8_t*)source;

    while (length--)
    {
        *d++ = *s++;
    }

    return destination;
}

void *Memory::MemorySet(void *destination, int32_t value, uint64_t length)
{
  uint8_t *ptr = (uint8_t*)destination;

  while (length-- > 0)
  {
    *ptr++ = value;
  }

  return destination;
}