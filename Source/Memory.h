#ifndef _MEMORY_H
#define _MEMORY_H

#include "Types.h"

class Memory
{
public:
    Memory();
    Memory(const Memory &memory);
    ~Memory();

    static void* MemorySet(void *destination, int32_t value, uint64_t length);
    static void* MemoryCopy(void *destination, const void *source, uint64_t length);
};

#endif // !_MEMORY_H