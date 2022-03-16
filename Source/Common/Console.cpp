#include <Common/Console.h>

#define INCREMENT_AND_CHECK_CURSOR_COORDINATES \
    if (++s_cursorCoordinates.m_x == 80)       \
    {                                          \
        s_cursorCoordinates.m_x = 0;           \
        s_cursorCoordinates.m_y++;             \
    }

#define RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED                                                             \
    if (s_cursorCoordinates.m_y == 25)                                                                              \
    {                                                                                                               \
        s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN; \
        s_cursorCoordinates.m_y = 0;                                                                                \
    }

uint8ptr_t Console::s_pVGAModeGraphicsAddressPosition = (uint8ptr_t)VGAModesAddresses::VGA_MODE_GRAPHICS_ADDRESS_BEGIN,
           Console::s_pVGAModeTextAddressPosition = (uint8ptr_t)VGAModesAddresses::VGA_MODE_TEXT_ADDRESS_BEGIN;
uint16ptr_t Console::s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;

size_t Console::s_size = {80, 25};
coordinates_t Console::s_cursorCoordinates = {0, 0};
uint8_t Console::s_textColor = (uint8_t)ConsoleTextColors::BACKGROUND_BLACK | (uint8_t)ConsoleTextColors::FOREGROUND_WHITE;

bool Console::s_isBlinking = false;

Console::Console()
{
}

Console::Console(const Console &console)
{
    Memory::Copy(this, &console, sizeof(console));
}

Console::~Console()
{
}

void Console::Write(uint32ptr_t pointer, const uint8_t base /* = 16 */)
{
    Write(Converter::Base10ToAnyBase(reinterpret_cast<int>(pointer), base));
}

void Console::ClearScreen()
{
    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN;

    for (uint8_t i = 0; i < s_size.m_height; i++)
    {
        for (uint8_t j = 0; j < s_size.m_width; j++)
        {
            *s_pVGAModeTextColoredAddressPosition = ((s_textColor - ((s_isBlinking) ? 128 : 0)) << 8) | ' ';
            s_pVGAModeTextColoredAddressPosition++;
        }
    }
}

size_t &Console::GetSize()
{
    return s_size;
}

coordinates_t &Console::GetCursorCoordinates()
{
    return s_cursorCoordinates;
}

uint8_t Console::GetTextColor()
{
    return s_textColor;
}

bool Console::GetIsBlinking()
{
    return s_isBlinking;
}

void Console::SetSize(const size_t &size)
{
    s_size = size;
}

void Console::SetIsBlinking(const bool isBlinking)
{
    s_isBlinking = isBlinking;
}

void Console::SetTextColor(const uint8_t color)
{
    s_textColor = color;
}

void Console::SetCursorCoodinates(const coordinates_t &coordinates)
{
    if (coordinates.m_x < s_size.m_width &&
        coordinates.m_y < s_size.m_height)
    {
        s_cursorCoordinates = coordinates;
    }
}

Console &Console::operator<<(const int8_t *string)
{
    Write(string);
}

void Console::Write(const uint8_t *string)
{
    for (uint32_t i = 0; string[i] != 0; i++)
    {
        if (string[i] == '\n')
        {
            s_pVGAModeTextColoredAddressPosition += s_size.m_width - s_cursorCoordinates.m_x - 1;

            s_cursorCoordinates.m_x = 79;
        }
        else
        {
            *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | string[i];
        }

        s_pVGAModeTextColoredAddressPosition++;
        INCREMENT_AND_CHECK_CURSOR_COORDINATES
        RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED
    }
}

void Console::Write(const int8_t ch)
{
    if (ch == '\n')
    {
        s_pVGAModeTextColoredAddressPosition += s_size.m_width - s_cursorCoordinates.m_x - 1;

        s_cursorCoordinates.m_x = 79;
    }
    else
    {
        *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | ch;
    }

    s_pVGAModeTextColoredAddressPosition++;
    INCREMENT_AND_CHECK_CURSOR_COORDINATES
    RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED
}

void Console::WriteLine(const int8_t ch)
{
    Write(ch);
}

void Console::Write(const uint8_t ch)
{
    if (ch == '\n')
    {
        s_pVGAModeTextColoredAddressPosition += s_size.m_width - s_cursorCoordinates.m_x - 1;

        s_cursorCoordinates.m_x = 79;
    }
    else
    {
        *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | ch;
    }

    s_pVGAModeTextColoredAddressPosition++;
    INCREMENT_AND_CHECK_CURSOR_COORDINATES
    RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED
}

void Console::WriteLine(const uint8_t ch)
{
    Write(ch);
}

void Console::WriteLine(const uint8_t *string)
{
    Write(string);
}

Console &Console::operator<<(const uint8_t *string)
{
    Write(string);
}

Console &Console::operator<<(const int8_t ch)
{
}

Console &Console::operator<<(const uint8_t ch)
{
}

Console &Console::operator<<(const int64_t integer)
{
    Write(integer);
}

Console &Console::operator<<(const uint32ptr_t pointer)
{
    Write(pointer);
}

Console &Console::operator>>(int8_t *&string)
{
}

Console &Console::operator>>(int64_t &integer)
{
}

void Console::ClearColumn(const uint8_t column)
{
    if (column >= s_size.m_width)
    {
        return;
    }

    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)((uint32_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN + (column - 1) * 2);

    for (uint8_t i = 0; i < s_size.m_height; i++)
    {
        *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | ' ';
        s_pVGAModeTextColoredAddressPosition += s_size.m_width;
    }
}

void Console::ClearRectangle(const rectangle_t &rectangle)
{
    if (rectangle.m_x + rectangle.m_width >= s_size.m_width ||
        rectangle.m_y + rectangle.m_height >= s_size.m_height)
    {
        return;
    }

    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)((uint32_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN + (rectangle.m_y - 1) * s_size.m_width * 2 + (rectangle.m_x - 1) * 2);

    for (uint8_t i = 0; i < rectangle.m_height; i++)
    {
        for (uint8_t j = 0; j < rectangle.m_width; j++)
        {
            *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | ' ';
            s_pVGAModeTextColoredAddressPosition++;
        }

        s_pVGAModeTextColoredAddressPosition += s_size.m_width - rectangle.m_width;
    }
}

void *Console::ReadKey()
{
    return nullptr;
}

const int64_t Console::Read()
{
    return 0;
}

const int8_t *Console::ReadLine()
{
    return nullptr;
}

void Console::WriteLine(const int8_t *string)
{
    Write(string + '\n');
}

void Console::WriteLine(const int64_t integer)
{
    Write(integer);
    Write('\n');
}

void Console::WriteLine(const uint32ptr_t pointer, const uint8_t base /* = 16 */)
{
    Write(pointer);
    Write('\n');
}

void Console::ClearLine(const uint8_t line)
{
    if (line >= s_size.m_height)
    {
        return;
    }

    s_pVGAModeTextColoredAddressPosition = (uint16ptr_t)((uint32_t)VGAModesAddresses::VGA_MODE_TEXT_COLORED_ADDRESS_BEGIN + s_size.m_width * (line - 1) * 2);

    for (uint8_t i = 0; i < s_size.m_width; i++)
    {
        *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | ' ';
        s_pVGAModeTextColoredAddressPosition++;
    }
}

void Console::Write(const int8_t *string)
{
    for (uint32_t i = 0; string[i] != 0; i++)
    {
        if (string[i] == '\n')
        {
            s_pVGAModeTextColoredAddressPosition += s_size.m_width - s_cursorCoordinates.m_x - 1;

            s_cursorCoordinates.m_x = 79;
        }
        else
        {
            *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | string[i];
        }

        s_pVGAModeTextColoredAddressPosition++;
        INCREMENT_AND_CHECK_CURSOR_COORDINATES
        RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED
    }
}

void Console::Write(int64_t integer)
{
    int64_t integerCopy = integer, firstLeftDigit = 1;

    if (integer < 0)
    {
        integer = -integer;
        integerCopy = integer;

        *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | '-';
        s_pVGAModeTextColoredAddressPosition++;
        INCREMENT_AND_CHECK_CURSOR_COORDINATES
        RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED
    }

    while (integer > 9)
    {
        firstLeftDigit *= 10;
        integer = Math::Divide(integer, 10);
    }

    while (firstLeftDigit != 0)
    {
        *s_pVGAModeTextColoredAddressPosition = (s_textColor << 8) | Math::Divide(integerCopy, firstLeftDigit) + '0';
        integerCopy = Math::Modulo(integerCopy, firstLeftDigit);
        firstLeftDigit = Math::Divide(firstLeftDigit, 10);

        s_pVGAModeTextColoredAddressPosition++;
        INCREMENT_AND_CHECK_CURSOR_COORDINATES
        RESET_VGAMTCAP_AND_CURSOR_COORDINATES_IF_NEEDED
    }
}