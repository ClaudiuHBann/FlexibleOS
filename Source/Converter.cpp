#include "Converter.h"

Converter::Converter()
{
	
}

Converter::Converter(const Converter& converter)
{
	Memory::Copy(this, &converter, sizeof(converter));
}

Converter::~Converter()
{

}

const int8_t* Converter::Base10ToAnyBase(int64_t value, const uint8_t base)
{
    static int8_t c_result[64];
	int8_t* string = c_result, *stringCopy = c_result, temporaryChar;
	int32_t temporaryValue;

	if (base < 2 || base > 36)
    {
        *c_result = 0;

        return c_result;
    }

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

	return c_result;
}

const int8_t* Converter::IntegerToString(int64_t integer)
{
    static int8_t c_string[20];
    uint8_t integerLength = 0;
    int64_t integerCopy = integer;

    while (integer != 0)
    {
        integerLength++;
        integer = Math::Divide(integer, 10);
    }

    for (int64_t i = integerLength - 1; i >= 0; i--)
    {
        c_string[i] = Math::Modulo(integerCopy, 10) + '0';
        integerCopy = Math::Divide(integerCopy, 10);
    }

    c_string[integerLength] = 0;

    return (const int8_t*)c_string;
}

int64_t Converter::StringToInteger(const int8_t *string)
{
	int64_t integer = 0;
	uint32_t stringLength = 0;

	while (string[stringLength++] != 0)

	for (uint32_t i = 0; i < stringLength; i++)
	{
		integer = integer * 10 + string[i] - '0';
	}

	return integer;
}