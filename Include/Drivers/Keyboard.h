#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <HardwareCommunication/InterruptManager.h>
#include <HardwareCommunication/Port.h>

#include <Common/Console.h>
#include <Common/Types.h>

class KeyboardDriver: public InterruptHandler
{
public:
    KeyboardDriver();
    KeyboardDriver(const KeyboardDriver &keyboardDriver);
    KeyboardDriver(InterruptManager &interruptManager);
    ~KeyboardDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);

private:
    Port8 commandPort;
    Port8 dataPort;
};

#endif // !_KEYBOARD_H