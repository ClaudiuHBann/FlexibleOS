#include "Math.h"

Math::Math()
{
}

Math::Math(const Math &math)
{
    Memory::Copy(this, &math, sizeof(math));
}

Math::~Math()
{
}

int64_t Math::Divide(int64_t dividend, int64_t divisor)
{
    bool isNegative = ((dividend < 0) ^ (divisor < 0)) ? true : false;

    dividend = Absolute(dividend);
    divisor = Absolute(divisor);

    int64_t quotient = 0, temporary = 0;

    for (int8_t i = 31; i >= 0; i--)
    {
        if (temporary + (divisor << i) <= dividend)
        {
            temporary += divisor << i;
            quotient |= 1LL << i;
        }
    }

    return (isNegative) ? -quotient : quotient;
}

int64_t Math::Absolute(int64_t number)
{
    return (number > 0) ? number : -number;
}

int64_t Math::Modulo(int64_t dividend, int64_t divisor)
{
    return (dividend - divisor * Divide(dividend, divisor));
}