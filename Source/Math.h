#ifndef _MATH_H
#define _MATH_H

#include "Types.h"

class Math
{
public:
    static int64_t Mod(int64_t num, int64_t divisor);
    static int64_t Absolute(int64_t integer);
    static int64_t Divide(int64_t dividend, int64_t divisor);
};

#endif // !_MATH_H