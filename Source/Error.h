/*+===================================================================
  File:      Error.h

  Summary:   Basic error detection and reporting.

  Classes:   Error.

  Copyright and Legal notices.
===================================================================+*/

#ifndef _ERROR_H
#define _ERROR_H

#include "Types.h"
#include "Memory.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Error

  Summary:  Basic error detection and report.

  Methods:  Error
              Default/Copy constructor.
            ~Error
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Error
{
public:
    Error();
    Error(const Error &error);
    ~Error();
};

#endif // !_ERROR_H