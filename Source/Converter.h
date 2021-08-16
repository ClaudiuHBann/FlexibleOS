#ifndef _CONVERTER_H
#define _CONVERTER_H

#include "Types.h"
#include "Math.h"
#include "Memory.h"

class Converter
{
public:
    Converter();
    Converter(const Converter& converter);
    ~Converter();

    static const int8_t* IntegerToString(int64_t integer);
    static int64_t StringToInteger(const int8_t* string);
    static const int8_t* Base10ToAnyBase(int64_t value, const uint8_t base);
};

#endif // !_CONVERTER_H