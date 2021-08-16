#include "Math.h"

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

int64_t Math::Absolute(int64_t integer)
{
    return (integer > 0) ? integer : -integer;
}

int64_t Math::Mod(int64_t num, int64_t divisor)
{
    return (num - divisor * Divide(num, divisor));
}