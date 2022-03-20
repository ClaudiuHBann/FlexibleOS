#ifndef _ERROR_H
#define _ERROR_H

#include <Common/Memory.h>
#include <Common/Types.h>

class Error
{
public:
    Error();
    Error(const Error &error);
    ~Error();
};

#endif // !_ERROR_H