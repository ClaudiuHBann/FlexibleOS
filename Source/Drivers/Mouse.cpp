#include <Drivers/Mouse.h>

MouseDriver::MouseDriver(InterruptManager &interruptManager) : InterruptHandler(0x2C, interruptManager),
                                                               dataPort(0x60),
                                                               commandPort(0x64)
{
    offset = 2;
    buttons = 0;

    static uint16_t *videoMemory = (uint16_t *)0xB8000;
    videoMemory[80 * 12 + 40] = ((videoMemory[80 * 12 + 40] & 0xF000) >> 4) |
                                ((videoMemory[80 * 12 + 40] & 0x0F00) << 4) |
                                (videoMemory[80 * 12 + 40] & 0x00FF);

    commandPort.Write(0xA8);
    commandPort.Write(0x20);
    uint8_t status = dataPort.Read() | 2;
    commandPort.Write(0x60);
    dataPort.Write(status);

    commandPort.Write(0xD4);
    dataPort.Write(0xF4);
    dataPort.Read();
}

MouseDriver::~MouseDriver()
{
}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandPort.Read();
    if (!(status & 0x20))
    {
        return esp;
    }

    static int8_t x = 40, y = 12;

    buffer[offset] = dataPort.Read();
    offset = (offset + 1) % 3;

    if (offset == 0)
    {
        static uint16_t *videoMemory = (uint16_t *)0xB8000;

        videoMemory[80 * y + x] = ((videoMemory[80 * y + x] & 0xF000) >> 4) |
                                  ((videoMemory[80 * y + x] & 0x0F00) << 4) |
                                  (videoMemory[80 * y + x] & 0x00FF);

        x += buffer[1];

        if (x < 0)
        {
            x = 0;
        }

        if (x >= 80)
        {
            x = 79;
        }

        y -= buffer[2];

        if (y < 0)
        {
            y = 0;
        }

        if (y >= 25)
        {
            y = 24;
        }

        videoMemory[80 * y + x] = ((videoMemory[80 * y + x] & 0xF000) >> 4) |
                                  ((videoMemory[80 * y + x] & 0x0F00) << 4) |
                                  (videoMemory[80 * y + x] & 0x00FF);

        for (uint8_t i = 0; i < 3; i++)
        {
            if ((buffer[0] & (0x01 << i)) != (buttons & (0x01 << i)))
            {
                videoMemory[80 * y + x] = ((videoMemory[80 * y + x] & 0xF000) >> 4) |
                                          ((videoMemory[80 * y + x] & 0x0F00) << 4) |
                                          (videoMemory[80 * y + x] & 0x00FF);
            }
        }

        buttons = buffer[0];
    }

    return esp;
}