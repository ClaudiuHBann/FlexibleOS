#ifndef _MATH_H
#define _MATH_H

#include <Common/Memory.h>
#include <Common/Types.h>
class Math
{
public:
    Math();
    Math(const Math &math);
    ~Math();

    static int64_t Modulo(int64_t dividend, int64_t divisor);
    static int64_t Absolute(int64_t number);
    static int64_t Divide(int64_t dividend, int64_t divisor);
};

#endif // !_MATH_H