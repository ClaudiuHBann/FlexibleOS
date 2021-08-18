#include "Console.h"

uint8ptr_t Console::s_pVGAModeGraphicsAddressPosition = (uint8ptr_t)VGAModesAddresses::VGA_MODE_GRAPHICS_ADDRESS_BEGIN,
           Console::s_pVGAModeTextAddressPosition = (uint8ptr_t)VGAModesAddresses::VGA_MODE_TEXT_ADDRESS_BEGIN;
uint16ptr_t Console::s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;

size_t Console::s_consoleSize = { 80, 25 };
coordinates_t Console::s_consoleCursorCoordinates = { 0, 0 };
uint8_t Console::s_consoleTextColor = (uint8_t)ConsoleTextColors::BACKGROUND_BLACK | (uint8_t)ConsoleTextColors::FOREGROUND_WHITE;

bool Console::s_isBlinking = false;

Console::Console()
{

}

Console::Console(const Console& console)
{
    Memory::Copy(this, &console, sizeof(console));
}

Console::~Console()
{
    
}

void Console::Print(uint32ptr_t pointer, const uint8_t base /* = 16 */)
{
    Print(Converter::Base10ToAnyBase(reinterpret_cast<int>(pointer), base));
}

void Console::Clear()
{
    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;

    for (uint8_t i = 0; i < s_consoleSize.height; i++)
    {
        for (uint8_t j = 0; j < s_consoleSize.width; j++)
        {
            *s_pVGAModeTextColoredAddressPosition = ((s_consoleTextColor >> 4) & 7) | ' ';
            s_pVGAModeTextColoredAddressPosition++;
        }
    }

    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;
    s_consoleCursorCoordinates = { 0, 0 };
}

size_t& Console::GetConsoleSize()
{
    return s_consoleSize;
}

coordinates_t& Console::GetConsoleCursorCoordinates()
{
    return s_consoleCursorCoordinates;
}

uint8_t Console::GetConsoleTextColor()
{
    return s_consoleTextColor;
}

bool Console::GetIsBlinking()
{
    return s_isBlinking;
}

void Console::ClearLine(const uint8_t line)
{
    if (line >= s_consoleSize.height)
    {
        return;
    }
    
    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN + (s_consoleSize.width * line);
    s_consoleCursorCoordinates = { static_cast<uint8_t>(line + 1), 0 };

    for (uint8_t i = 0; i < s_consoleSize.width; i++)
    {
        *s_pVGAModeTextColoredAddressPosition = ((s_consoleTextColor >> 4) & 7) | ' ';
        s_pVGAModeTextColoredAddressPosition++;
    }
}

void Console::Print(const int8_t* string)
{
    for(uint32_t i = 0; string[i] != 0; i++)
    {
        *s_pVGAModeTextColoredAddressPosition = s_consoleTextColor | string[i];

        s_pVGAModeTextColoredAddressPosition++;
        if (s_pVGAModeTextColoredAddressPosition > (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_END)
        {
            s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;
        }
    }
}

void Console::Print(int64_t integer)
{
    int64_t firstLeftDigit = 1, integerCopy = integer;
    bool isNegative = false;

    if (integer < 0)
    {
        isNegative = true;
        integer = -integer;
        integerCopy = integer;
    }

    while (integer >= 9)
    {
        firstLeftDigit *= 10;
        integer = Math::Divide(integer, 10);
    }

    if (isNegative)
    {
        if (s_pVGAModeTextColoredAddressPosition > (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_END)
        {
            s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;
        }

        *s_pVGAModeTextColoredAddressPosition++ = s_consoleTextColor | '-';
    }

    while (integerCopy != 0)
    {
        *s_pVGAModeTextColoredAddressPosition = s_consoleTextColor | int8_t(Math::Divide(integerCopy, firstLeftDigit) + '0');
        integerCopy = Math::Modulo(integerCopy, firstLeftDigit);
        firstLeftDigit = Math::Divide(firstLeftDigit, 10);
        
        s_pVGAModeTextColoredAddressPosition++;
        if (s_pVGAModeTextColoredAddressPosition > (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_END)
        {
            s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;
        }
    }
}