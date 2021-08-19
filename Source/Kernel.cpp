#include "Types.h"
#include "Console.h"
#include "GlobalDescriptorTable.h"

extern "C" constructor_t constructorsStart, constructorsEnd;

extern "C" void ConstructorsCall()
{
    for(constructor_t* i = &constructorsStart; i != &constructorsEnd; i++)
    {
        (*i)();
    }
}

extern "C" void KernelMain(const void* multibootStructure, uint32_t)
{
    multibootInfo_t multibootInfo = *(pMultibootInfo_t)multibootStructure;

    GlobalDescriptorTable gdt;

    Console console;

    while (true)
    {

    }
}