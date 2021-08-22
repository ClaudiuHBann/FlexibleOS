#include "Types.h"
#include "Console.h"
#include "GlobalDescriptorTable.h"
#include "InterruptManager.h"

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

    GlobalDescriptorTable globalDescriptorTable;
    InterruptManager interruptManager(globalDescriptorTable);



    interruptManager.Activate();

    Console console;
    console << "Hello from FlexibleOS!\n";

    while (true)
    {

    }
}