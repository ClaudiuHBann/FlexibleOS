#ifndef _MOUSE_H
#define _MOUSE_H

#include <HardwareCommunication/InterruptManager.h>
#include <HardwareCommunication/Port.h>

#include <Drivers/Driver.h>

#include <Common/Console.h>
#include <Common/Types.h>

typedef struct MousePacket
{
    uint8_t x, y, z;
    uint8_t buttons;
} MousePacket;

class MouseEventHandler
{
public:
    MouseEventHandler();
    ~MouseEventHandler();

    virtual void OnActivate();

    virtual void OnMouseDown(uint8_t button);
    virtual void OnMouseUp(uint8_t button);
    virtual void OnMouseMove(uint8_t x, uint8_t y);
};

class MouseDriver : public Driver, public InterruptHandler
{
public:
    MouseDriver();
    MouseDriver(const MouseDriver &mouseDriver);
    MouseDriver(InterruptManager &interruptManager);
    ~MouseDriver();

    bool *GetMouseButtonsState() { return mouseButtonsState; }

    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();

private:
    Port8 commandPort;
    Port8 dataPort;

    uint8_t buffer[4];
    uint8_t offset = 0;
    uint8_t buttons = 0;
    int8_t wheel = 0;

    bool hasWheel = false;
    bool mouseButtonsState[3];
};

#endif // !_MOUSE_H