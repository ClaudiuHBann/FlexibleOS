#include "Console.h"

uint16_t* Console::videoMemoryAddressStart = (uint16_t*)0xB8000;
uint16_t* Console::lastVideoMemoryAddressPosition = videoMemoryAddressStart;
uint16_t* Console::videoMemoryAddressEnd = (uint16_t*)0xBFFFF;

void Console::Print(const int8_t* string)
{
    for(uint32_t i = 0; string[i] != 0; i++)
    {
        *lastVideoMemoryAddressPosition = (*lastVideoMemoryAddressPosition & 0xFF00) | string[i];

        lastVideoMemoryAddressPosition++;
        if (lastVideoMemoryAddressPosition > videoMemoryAddressEnd)
        {
            lastVideoMemoryAddressPosition = videoMemoryAddressStart;
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

    if (lastVideoMemoryAddressPosition > videoMemoryAddressEnd)
    {
        lastVideoMemoryAddressPosition = videoMemoryAddressStart;
    }

    if (isNegative)
    {
        *lastVideoMemoryAddressPosition++ = (*lastVideoMemoryAddressPosition & 0xFF00) | '-';
    }

    while (integerCopy != 0)
    {
        *lastVideoMemoryAddressPosition = (*lastVideoMemoryAddressPosition & 0xFF00) | char(Math::Divide(integerCopy, firstLeftDigit) + '0');
        integerCopy = Math::Mod(integerCopy, firstLeftDigit);
        firstLeftDigit = Math::Divide(firstLeftDigit, 10);
        
        lastVideoMemoryAddressPosition++;
        if (lastVideoMemoryAddressPosition > videoMemoryAddressEnd)
        {
            lastVideoMemoryAddressPosition = videoMemoryAddressStart;
        }
    }
}