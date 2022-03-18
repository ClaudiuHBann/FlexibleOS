#include <HardwareCommunication/InterruptManager.h>

#include <Drivers/VideoGraphicsArray.h>
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

    VideoGraphicsArray vga;
    vga.SetGraphicMode(VGA_MODE_GRAPHIC_320x200x256);

    uint8_t buffer[200 * 320];
    uint8_t *VGA = (uint8_t *)0xA0000;
    while (true)
    {
        for (int32_t y = 0; y < 200; y++)
            for (int32_t x = 0; x < 320; x++)
                buffer[y * 320 + x] = 0;

        for (int32_t y = 0; y < 200; y++)
            for (int32_t x = 0; x < 320; x++)
                buffer[y * 320 + x] = y % 64;

        Memory::Copy(VGA, buffer, 200 * 320);
    }
}