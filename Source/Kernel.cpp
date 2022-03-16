#include <HardwareCommunication/InterruptManager.h>

#include <Drivers/Keyboard.h>
#include <Drivers/Mouse.h>

#include <Common/Console.h>
#include <Common/Types.h>

#include <GlobalDescriptorTable.h>

extern "C" constructor_t constructorsStart, constructorsEnd;

extern "C" void ConstructorsCall()
{
    for (constructor_t *i = &constructorsStart; i != &constructorsEnd; i++)
    {
        (*i)();
    }
}

extern "C" void KernelMain(const void *multibootStructure, uint32_t)
{
    multibootInfo_t multibootInfo = *(pMultibootInfo_t)multibootStructure;

    GlobalDescriptorTable globalDescriptorTable;
    InterruptManager interruptManager(globalDescriptorTable);

    KeyboardDriver keyboardDriver(interruptManager);
    MouseDriver mouseDriver(interruptManager);

    interruptManager.Activate();

    Console console;
    console << "Flexible@OS ~ $ ";

    while (true)
    {
    }
}