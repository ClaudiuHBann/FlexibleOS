#include "Everything.h" 

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

int64_t Math::Divide(int64_t dividend, int64_t divisor)
{
    int32_t sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;

    dividend = Absolute(dividend);
    divisor = Absolute(divisor);

    int64_t quotient = 0, temp = 0;

    for (int32_t i = 31; i >= 0; i--)
    {
    	if (temp + (divisor << i) <= dividend)
        {
    	    temp += divisor << i;
    	    quotient |= 1LL << i;
    	}
    }

    return (sign == -1) ? -quotient : quotient;
}

inline int64_t Math::Absolute(int64_t integer)
{
    return (integer > 0) ? integer : -integer;
}

inline int64_t Math::Mod(int64_t num, int64_t divisor)
{
    return (num - divisor * Divide(num, divisor));
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

const int8_t* Converter::Base10ToAnyBase(int64_t value, const uint8_t base)
{
    static char result[64];

	if (base < 2 || base > 36)
    {
        *result = 0;

        return result;
    }

	char* string = result, *stringCopy = result, temporaryChar;
	int temporaryValue;

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

void *Memory::MemoryCopy(void *destination, const void *source, uint64_t length)
{
    int8_t *d = (int8_t*)destination;
    const int8_t *s = (int8_t*)source;

    while (length--)
    {
        *d++ = *s++;
    }

    return destination;
}

const char* Converter::IntegerToString(int64_t integer)
{
    uint8_t integerLength = 0;
    int64_t integerCopy = integer;

    while (integer != 0)
    {
        integerLength++;
        integer = Math::Divide(integer, 10);
    }

    static char string[20];
    for (int64_t i = integerLength - 1; i >= 0; i--)
    {
        string[i] = char(Math::Mod(integerCopy, 10) + '0');
        integerCopy = Math::Divide(integerCopy, 10);
    }

    string[integerLength] = 0;

    return (const char*)string;
}

void *Memory::MemorySet(void *destination, int32_t value, uint64_t length)
{
  uint8_t *ptr = (uint8_t*)destination;

  while (length-- > 0)
  {
    *ptr++ = value;
  }

  return destination;
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