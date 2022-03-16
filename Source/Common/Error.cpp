#include <Common/Error.h>

Error::Error()
{
}

Error::Error(const Error &error)
{
    Memory::Copy(this, &error, sizeof(error));
}

Error::~Error()
{
}