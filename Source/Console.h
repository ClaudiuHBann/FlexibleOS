#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Types.h"
#include "Math.h"

class Console
{
public:
    Console();
    Console(const Console& console);
    virtual ~Console();

    static void Print(const int8_t* string);
    static void Print(int64_t integer);

private:
    static uint16_t* videoMemoryAddressStart, *lastVideoMemoryAddressPosition, *videoMemoryAddressEnd;
};

#endif // !_CONSOLE_H