#include "Types.h"
#include "Console.h"
#include "GlobalDescriptorTable.h"

extern "C" Constructor constructorsStart, constructorsEnd;

extern "C" void ConstructorsCall()
{
    for(Constructor* i = &constructorsStart; i != &constructorsEnd; i++)
    {
        (*i)();
    }
}

extern "C" void KernelMain(const void* multibootStructure, uint32_t)
{
    MULTIBOOT_INFO multibootInfo = *(MULTIBOOT_INFO*)multibootStructure;

    GlobalDescriptorTable gdt;

    Console::Print("Hello from SimpleOS!");
        
    while (true)
    {

    }
}