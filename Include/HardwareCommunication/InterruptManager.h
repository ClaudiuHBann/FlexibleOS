#ifndef _INTERRUPT_MANAGER_H
#define _INTERRUPT_MANAGER_H

#include <HardwareCommunication/Port.h>

#include <Common/Console.h>
#include <Common/Memory.h>
#include <Common/Types.h>

#include <GlobalDescriptorTable.h>

class InterruptHandler;

class InterruptManager
{
    friend class InterruptHandler;

protected:
    static InterruptManager *s_activeInterruptManager;

    InterruptHandler *interruptHandlers[256];

    struct gateDescriptor_s
    {
        uint16_t m_handlerAddressLowBits;
        uint16_t m_gdtCodeSegmentSelector;
        uint8_t m_reserved;
        uint8_t m_access;
        uint16_t m_handlerAddressHighBits;
    } __attribute__((packed));

    static gateDescriptor_s s_interruptDescriptorTable[256];

    struct interruptDescriptorTable_s
    {
        uint16_t m_size;
        uint32_t m_base;
    } __attribute__((packed));

    static void SetInterruptDescriptorTableEntry(uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset, void (*handler)(), uint8_t descriptorPrivilegeLevel, uint8_t descriptorType);

    Port8Slow picMasterCommand;
    Port8Slow picMasterData;
    Port8Slow picSlaveCommand;
    Port8Slow picSlaveData;

public:
    InterruptManager();
    InterruptManager(const InterruptManager &interruptManager);
    InterruptManager(GlobalDescriptorTable &globalDescriptorTable);
    ~InterruptManager();

    void Activate();
    void Deactivate();

    static uint32_t HandleInterrupt(uint8_t interruptNumber, uint32_t esp);
    uint32_t DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp);

    static void InterruptIgnore();

    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
    static void HandleInterruptRequest0x0C();
};

class InterruptHandler
{
protected:
    uint8_t interruptNumber;
    InterruptManager *interruptManager;

    InterruptHandler();
    InterruptHandler(uint8_t interruptNumber, InterruptManager &interruptManager);
    InterruptHandler(const InterruptHandler &interruptHandler);
    ~InterruptHandler();

public:
    virtual uint32_t HandleInterrupt(uint32_t esp);
};

#endif // !_INTERRUPT_MANAGER_H