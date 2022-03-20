#include <Drivers/Driver.h>

void DriverManager::Add(Driver *driver)
{
    drivers[driversNum++] = driver;
}

void DriverManager::ActivateAll()
{
    for (uint8_t i = 0; i < driversNum; i++)
    {
        drivers[i]->Activate();
    }
}