#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "Types.h"
#include "Port.h"
#include "Console.h"
#include "InterruptManager.h"

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