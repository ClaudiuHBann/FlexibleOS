/*+===================================================================
  File:      Converter.h

  Summary:   Base conversions.

  Classes:   Converter.

  Copyright and Legal notices.
===================================================================+*/

#ifndef _CONVERTER_H
#define _CONVERTER_H

#include "Types.h"
#include "Math.h"
#include "Memory.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Converter

  Summary:  Converts a base data type to another base data type.

  Methods:  IntegerToString
              Converts an integer into a string.
            StringToInteger
              Converts a string into an integer.
            Base10ToAnyBase
              Converts a decimal integer into any base.

            Converter
              Default/Copy donstructor.
            ~Converter
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Converter
{
public:
    Converter();
    Converter(const Converter &converter);
    ~Converter();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Converter::IntegerToString

      Summary:  Converts an integer to a const string.

      Args:     int64_t integer
                  The integer which will be converted.

     Returns:  const int8_t*
                The integer as a const string.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static const int8_t *IntegerToString(int64_t integer);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Converter::StringToInteger

      Summary:  Converts a string to an integer.

      Args:     const int8_t*
                  The string which will be converted.

     Returns:  int64_t
                The string as an integer.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static int64_t StringToInteger(const int8_t *string);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Converter::Base10ToAnyBase

      Summary:  Converts a decimal integer into any base.

      Args:     int64_t integer
                  The integer which will be converted.
                const uint8_t base
                  The base to which will be converted.

     Returns:  const int8_t*
                The integer in the base as a const string representation.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static const int8_t *Base10ToAnyBase(int64_t integer, const uint8_t base);
};

#endif // !_CONVERTER_H