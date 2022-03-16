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

    if (key >> 7)
    {
        Console c;
        bool *modifiers = Console::GetModifiers();

        switch (key - (1 << 7))
        {
        case 0x3A:
            modifiers[0] = !modifiers[0];
            break;
        case 0x2A:
            modifiers[1] = false;
            break;
        case 0x36:
            modifiers[2] = false;
            break;
        default:
            break;
        }
    }

    if (key < 0x80)
    {
        Console c;
        bool *modifiers = Console::GetModifiers();

        const char *line2thLower = "1234567890-=";
        const char *line3thLower = "qwertyuiop[]";
        const char *line4thLower = "asdfghjkl;'";
        const char *line5thLower = "zxcvbnm,./";

        const char *line2thUpper = "!@#$%^&*()_+";
        const char *line3thUpper = "QWERTYUIOP{}";
        const char *line4thUpper = "ASDFGHJKL:\"";
        const char *line5thUpper = "ZXCVBNM<>?";

        if (key >= 0x02 && key <= 0x0D)
        {
            if ((modifiers[0] || modifiers[1] || modifiers[2]) && !((modifiers[0] && modifiers[1]) || (modifiers[0] && modifiers[2])))
            {
                c << line2thUpper[key - 0x02];
            }
            else
            {
                c << line2thLower[key - 0x02];
            }

            return esp;
        }

        if (key >= 0x10 && key <= 0x1B)
        {
            if ((modifiers[0] || modifiers[1] || modifiers[2]) && !((modifiers[0] && modifiers[1]) || (modifiers[0] && modifiers[2])))
            {
                c << line3thUpper[key - 0x10];
            }
            else
            {
                c << line3thLower[key - 0x10];
            }

            return esp;
        }

        if (key >= 0x1E && key <= 0x28)
        {
            if ((modifiers[0] || modifiers[1] || modifiers[2]) && !((modifiers[0] && modifiers[1]) || (modifiers[0] && modifiers[2])))
            {
                c << line4thUpper[key - 0x1E];
            }
            else
            {
                c << line4thLower[key - 0x1E];
            }

            return esp;
        }

        if (key >= 0x2C && key <= 0x35)
        {
            if ((modifiers[0] || modifiers[1] || modifiers[2]) && !((modifiers[0] && modifiers[1]) || (modifiers[0] && modifiers[2])))
            {
                c << line5thUpper[key - 0x2C];
            }
            else
            {
                c << line5thLower[key - 0x2C];
            }

            return esp;
        }

        switch (key)
        {
        case 0x01:
            c.ClearScreen();
            break;
        case 0x0F:
            c << "    ";
            break;
        case 0x2B:
            if ((modifiers[0] || modifiers[1] || modifiers[2]) && !((modifiers[0] && modifiers[1]) || (modifiers[0] && modifiers[2])))
            {
                c << '|';
            }
            else
            {
                c << '\\';
            }
            break;
        case 0x1C:
            c << "\n";
            break;
        case 0x39:
            c << " ";
            break;
        case 0x29:
            c << "`";
            break;
        case 0x37:
            c << "*";
            break;
        case 0x4A:
            c << "-";
            break;
        case 0x4E:
            c << "+";
            break;

        case 0x3A:
            break;
        case 0x2A:
            modifiers[1] = true;
            break;
        case 0x36:
            modifiers[2] = true;
            break;

        default:
            char message[] = "KEYBOARD 0x00";
            const char *hex = "0123456789ABCDEF";
            message[11] = hex[(key >> 4) & 0x0F];
            message[12] = hex[key & 0x0F];

            c << message << " ";
            break;
        }
    }

    return esp;
}