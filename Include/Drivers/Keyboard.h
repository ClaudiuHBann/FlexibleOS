#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <HardwareCommunication/InterruptManager.h>
#include <HardwareCommunication/Port.h>

#include <Drivers/Driver.h>

#include <Common/Console.h>
#include <Common/Types.h>

class KeyboardEventHandler
{
public:
    KeyboardEventHandler();
    ~KeyboardEventHandler();

    virtual void OnKeyDown(char c);
    virtual void OnKeyUp(char c);
};

class KeyboardDriver : public Driver, public InterruptHandler
{
public:
    KeyboardDriver();
    KeyboardDriver(const KeyboardDriver &keyboardDriver);
    KeyboardDriver(InterruptManager &interruptManager);
    ~KeyboardDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();

    static bool* GetModifiers() { return s_modifiers; }

private:
    Port8 commandPort;
    Port8 dataPort;

    static bool s_modifiers[3];

    KeyboardEventHandler *keyboardEventHandler;
};

#endif // !_KEYBOARD_H