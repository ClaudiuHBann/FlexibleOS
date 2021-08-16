#include "Everything.h"

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
    MultibootInfo multibootInfo = *(MultibootInfo*)multibootStructure;

    while (true)
    {    
        //Console::Print("Hello from SimpleOS!");
    }
}