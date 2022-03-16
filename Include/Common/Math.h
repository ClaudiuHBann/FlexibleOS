/*+===================================================================
  File:      Math.h

  Summary:   Basic mathematical operations.

  Classes:   Math

  Copyright and Legal notices.
===================================================================+*/

#ifndef _MATH_H
#define _MATH_H

#include <Common/Memory.h>
#include <Common/Types.h>

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Math

  Summary:  Basic mathematical operations.

  Methods:  Modulo
              Returns the remainder of an integer division.
            Absolute
              Returns the real number taken without a sign.
            Divide
              Returns the result between two values division.

            Math
              Default/Copy constructor.
            ~Math
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Math
{
public:
    Math();
    Math(const Math &math);
    ~Math();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Math::Modulo

      Summary:  Calculates the remainder of an integer division.

      Args:     int64_t dividend
                  The number that is being divided.
                int64_t divisor
                  The number that it is being divided by.

      Returns:  int64_t
                  The remainder of the integer division.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static int64_t Modulo(int64_t dividend, int64_t divisor);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Math::Absolute

      Summary:  Calculates the real number taken without a sign.

      Args:     int64_t number
                  The number whose absolute value to find out.

      Returns:  int64_t
                  The real number taken without a sign.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static int64_t Absolute(int64_t number);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Math::Divide

      Summary:  Calculates the result between two values division.

      Args:     int64_t dividend
                  The number that is being divided.
                int64_t divisor
                  The number that it is being divided by.

      Returns:  int64_t
                  The result between two values division.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static int64_t Divide(int64_t dividend, int64_t divisor);
};

#endif // !_MATH_H