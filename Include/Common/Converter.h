#ifndef _CONVERTER_H
#define _CONVERTER_H

#include <Common/Memory.h>
#include <Common/Types.h>
#include <Common/Math.h>

class Converter
{
public:
    Converter();
    Converter(const Converter &converter);
    ~Converter();

    static const int8_t *IntegerToString(int64_t integer);
    static int64_t StringToInteger(const int8_t *string);
    static const int8_t *Base10ToAnyBase(int64_t integer, const uint8_t base);
};

#endif // !_CONVERTER_H