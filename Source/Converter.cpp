#include "Converter.h"

Converter::Converter()
{
	
}

Converter::Converter(const Converter& converter)
{
	Memory::MemoryCopy(this, &converter, sizeof(converter));
}

Converter::~Converter()
{

}

const int8_t* Converter::Base10ToAnyBase(int64_t value, const uint8_t base)
{
    static int8_t result[64];

	if (base < 2 || base > 36)
    {
        *result = 0;

        return result;
    }

	int8_t* string = result, *stringCopy = result, temporaryChar;
	int32_t temporaryValue;

	do
    {
		temporaryValue = value;
		value = Math::Divide(value, base);
		*string++ = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + (temporaryValue - value * base)];
	} while ( value );

	if (temporaryValue < 0)
    {
        *string++ = '-';
    }

	*string-- = 0;

	while(stringCopy < string)
    {
		temporaryChar = *string;
		*string--= *stringCopy;
		*stringCopy++ = temporaryChar;
	}

	return result;
}

const int8_t* Converter::IntegerToString(int64_t integer)
{
    uint8_t integerLength = 0;
    int64_t integerCopy = integer;

    while (integer != 0)
    {
        integerLength++;
        integer = Math::Divide(integer, 10);
    }

    static int8_t string[20];
    for (int64_t i = integerLength - 1; i >= 0; i--)
    {
        string[i] = int8_t(Math::Mod(integerCopy, 10) + '0');
        integerCopy = Math::Divide(integerCopy, 10);
    }

    string[integerLength] = 0;

    return (const int8_t*)string;
}

int64_t Converter::StringToInteger(const int8_t *string)
{
	int64_t integer = 0;
	uint32_t stringLength = 0;

	while (string[stringLength] != 0)
	{
		stringLength++;
	}

	for (uint32_t i = 0; i < stringLength; i++)
	{
		integer = integer * 10 + string[i] - '0';
	}

	return integer;
}