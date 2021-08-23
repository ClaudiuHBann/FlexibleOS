/*+===================================================================
  File:      InterruptManager.h

  Summary:   Basic CPU interrupts manager.

  Classes:   InterruptManager.

  Copyright and Legal notices.
===================================================================+*/

#ifndef _INTERRUPT_MANAGER_H
#define _INTERRUPT_MANAGER_H

#include "Console.h"
#include "Memory.h"
#include "Port.h"
#include "GlobalDescriptorTable.h"
#include "Types.h"

class InterruptHandler;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    InterruptManager

  Summary:  Manages the CPU interrupts.

  Methods:  SetInterruptDescriptorTableEntry
              Sets the interrupt descriptor table entry.
            Activate
              Activates the handled interrupts.
            HandleInterrupt
              Handles the interrupt.
            InterruptIgnore
              Ignores the interrupt.
            HandleInterruptRequestX
              Handles the interrupt for the X request.

            InterruptManager
              Default/Copy constructor.
            InterruptManager
              Sets the interrups with the specific GlobalDescriptorTable.
            ~InterruptManager
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
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

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   InterruptManager::SetInterruptDescriptorTableEntry

      Summary:  Sets the interrupt descriptor table entry.

      Args:     uint8_t interruptNumber
                  The interrupt number.
                uint16_t codeSegmentSelectorOffset
                  The code segment selector offset.
                void* handler
                  The handler function for the interrupt.
                uint8_t descriptorPrivilegeLevel
                  The descriptor privilege level.
                uint8_t descriptorType
                  The descriptor type.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
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

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   InterruptManager::Activate

      Summary:  Activates the handled interrupts.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    void Activate();
    void Deactivate();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   InterruptManager::HandleInterrupt

      Summary:  Handles the specific interrupt.

      Args:     uint8_t interruptNumber
                  The interrupt number.
                uint32_t esp
                  The extended stack pointer.

      Returns:  uint32_t
                  .
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static uint32_t HandleInterrupt(uint8_t interruptNumber, uint32_t esp);
    uint32_t DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   InterruptManager::InterruptIgnore

      Summary:  Ingores the Interrupt.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static void InterruptIgnore();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   InterruptManager::HandleInterruptRequestX

      Summary:  Handles the X interrupt.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
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