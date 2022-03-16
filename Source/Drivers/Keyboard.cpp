#include <Drivers/Keyboard.h>

KeyboardDriver::KeyboardDriver(InterruptManager &interruptManager) : InterruptHandler(0x21, interruptManager),
                                                                     dataPort(0x60),
                                                                     commandPort(0x64)
{
    while (commandPort.Read() & 0x1)
    {
        dataPort.Read();
    }

    commandPort.Write(0xAE);
    commandPort.Write(0x20);
    uint8_t status = (dataPort.Read() | 1) & ~0x10;
    commandPort.Write(0x60);
    dataPort.Write(status);
    dataPort.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver()
{
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataPort.Read();

    if (key < 0x80)
    {
        switch (key)
        {
        case 0xFA:
        case 0xC5:
        case 0x45:
            break;

        default:
            // char message[] = "KEYBOARD 0x00";
            // const char *hex = "0123456789ABCDEF";
            // message[11] = hex[(key >> 4) & 0x0F];
            // message[12] = hex[key & 0x0F];

            // Console c;
            // c << message << " = " << key << " ";

            Console c;
            c << key;

            break;
        }
    }

    return esp;
}