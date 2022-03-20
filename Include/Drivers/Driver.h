#ifndef _DRIVER_H
#define _DRIVER_H

#include <Common/Types.h>

class Driver
{
public:
    Driver() {}
    ~Driver() {}

    virtual int32_t Reset() { return 0; }
    virtual void Activate() {}
    virtual void Deactivate() {}
};

class DriverManager
{
public:
    DriverManager() {}
    ~DriverManager() {}

    void ActivateAll();
    void Add(Driver *driver);

private:
    Driver *drivers[255];
    uint8_t driversNum = 0;
};

#endif // !_DRIVER_H