#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Types.h"
#include "Math.h"
#include "Memory.h"
#include "Converter.h"

#define BLINKING 0x80

enum class VGAModes
{
    VGA_MODE_GRAPHICS =     0,
    VGA_MODE_TEXT =         1,
    VGA_MODE_TEXT_COLORED = 2
};

enum class VGAModesAddresses
{
    VGA_MODE_GRAPHICS_ADDRESS_BEGIN =   0xA0000,
    VGA_MODE_GRAPHICS_ADDRESS_END =     0xAFFFF,

    VGA_MODE_TEXT_ADDRESS_BEGIN =   0xB0000,
    VGA_MODE_TEXT_ADDRESS_END =     0xB7FFF,

    VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN =   0xB8000,
    VGA_MODE_TEXT_COLORED_ADDRESS_END =     0xBFFFF
};

enum class ConsoleTextColors
{
    BACKGROUND_BLACK =      0x00,
    BACKGROUND_BLUE =       0x10,
    BACKGROUND_GREEN =      0x20,
    BACKGROUND_CYAN =       0x30,
    BACKGROUND_RED =        0x40,
    BACKGROUND_MAGENTA =    0x50,
    BACKGROUND_YELLOW =     0x60,
    BACKGROUND_WHITE =      0x70,

    FOREGROUND_BLACK =      0X00,
    FOREGROUND_NAVY =       0X01,
    FOREGROUND_GREEN =      0X02,
    FOREGROUND_TEAL =       0X03,
    FOREGROUND_MAROON =     0X04,
    FOREGROUND_PURPLE =     0X05,
    FOREGROUND_OLIVE =      0X06,
    FOREGROUND_SILVER =     0X07,
    FOREGROUND_GRAY =       0X08,
    FOREGROUND_BLUE =       0X09,
    FOREGROUND_LIME =       0X0A,
    FOREGROUND_CYAN =       0X0B,
    FOREGROUND_ORANGE =     0X0C,
    FOREGROUND_MAGENTA =    0X0D,
    FOREGROUND_YELLOW =     0X0E,
    FOREGROUND_WHITE =      0X0F
};

class Console
{
public:
    Console();
    Console(const Console& console);
    ~Console();

    static void SetVGAMode(const VGAModes vgaMode);

    static void Print(const int8_t* string);
    static void Print(int64_t integer);
    static void Print(uint32ptr_t pointer, const uint8_t base = 16);

    static void Clear();
    static void ClearLine(const uint8_t line);

    static size_t& GetConsoleSize();
    static coordinates_t& GetConsoleCursorCoordinates();
    static uint8_t GetConsoleTextColor();
    static bool GetIsBlinking();


    static bool SetIsBlinking(const bool isBlinking);

private:
    static uint8ptr_t s_pVGAModeGraphicsAddressPosition, s_pVGAModeTextAddressPosition;
    static uint16ptr_t s_pVGAModeTextColoredAddressPosition;

    static size_t s_consoleSize;
    static coordinates_t s_consoleCursorCoordinates;
    static uint8_t s_consoleTextColor;

    static bool s_isBlinking;
};

#endif // !_CONSOLE_H