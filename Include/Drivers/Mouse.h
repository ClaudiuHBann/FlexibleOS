#ifndef _MOUSE_H
#define _MOUSE_H

#include <HardwareCommunication/InterruptManager.h>
#include <HardwareCommunication/Port.h>

#include <Common/Console.h>
#include <Common/Types.h>

class MouseDriver : public InterruptHandler
{
public:
    MouseDriver();
    MouseDriver(const MouseDriver &mouseDriver);
    MouseDriver(InterruptManager &interruptManager);
    ~MouseDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);

private:
    Port8 commandPort;
    Port8 dataPort;

    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;
};

#endif // !_MOUSE_H