#include "InterruptManager.h"

InterruptManager::gateDescriptor_s InterruptManager::s_interruptDescriptorTable[256];
InterruptManager *InterruptManager::s_activeInterruptManager = nullptr;

InterruptManager::InterruptManager()
{
}

InterruptManager::InterruptManager(const InterruptManager &interruptManager)
{
    Memory::Copy(this, &interruptManager, sizeof(interruptManager));
}

void InterruptManager::Activate()
{
    if (s_activeInterruptManager != nullptr)
    {
        s_activeInterruptManager->Deactivate();
    }

    s_activeInterruptManager = this;

    asm("sti");
}

void InterruptManager::Deactivate()
{
    if (s_activeInterruptManager == this)
    {
        s_activeInterruptManager = nullptr;

        asm("cli");
    }
}

InterruptManager::InterruptManager(GlobalDescriptorTable &globalDescriptorTable)
    : picMasterCommand(0x20),
      picMasterData(0x21),
      picSlaveCommand(0xA0),
      picSlaveData(0xA1)
{
    uint16_t codeSegment = globalDescriptorTable.GetCodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for (uint16_t i = 0; i < 256; i++)
    {
        interruptHandlers[i] = nullptr;
        SetInterruptDescriptorTableEntry(i, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }

    SetInterruptDescriptorTableEntry(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x2C, codeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);

    picMasterCommand.Write(0x11);
    picSlaveCommand.Write(0x11);

    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);

    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

    interruptDescriptorTable_s interruptDescriptorTable;
    interruptDescriptorTable.m_size = 256 * sizeof(gateDescriptor_s) - 1;
    interruptDescriptorTable.m_base = (uint32_t)s_interruptDescriptorTable;

    asm volatile("lidt %0"
                 :
                 : "m"(interruptDescriptorTable));
}

InterruptManager::~InterruptManager()
{
}

void InterruptManager::SetInterruptDescriptorTableEntry(uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset, void (*handler)(), uint8_t descriptorPrivilegeLevel, uint8_t descriptorType)
{
    const uint8_t IDT_DESC_PRESENT = 0x80;

    s_interruptDescriptorTable[interruptNumber].m_handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    s_interruptDescriptorTable[interruptNumber].m_handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
    s_interruptDescriptorTable[interruptNumber].m_gdtCodeSegmentSelector = codeSegmentSelectorOffset;
    s_interruptDescriptorTable[interruptNumber].m_access = IDT_DESC_PRESENT | descriptorType | ((descriptorPrivilegeLevel & 3) << 5);
    s_interruptDescriptorTable[interruptNumber].m_reserved = 0;
}

uint32_t InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp)
{
    if (s_activeInterruptManager != nullptr)
    {
        return s_activeInterruptManager->DoHandleInterrupt(interruptNumber, esp);
    }

    return esp;
}

uint32_t InterruptManager::DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp)
{
    if (interruptHandlers[interruptNumber] != 0)
    {
        esp = interruptHandlers[interruptNumber]->HandleInterrupt(esp);
    }
    else if (interruptNumber != 0x20)
    {
        char *message = "UNHANDLED INTERRUPT 0x00";
        const char *hex = "0123456789ABCDEF";
        message[22] = hex[(interruptNumber >> 4) & 0x0F];
        message[23] = hex[interruptNumber & 0x0F];

        Console::Write(message);
    }

    if (0x20 <= interruptNumber && interruptNumber < 0x30)
    {
        picMasterCommand.Write(0x20);

        if (0x28 <= interruptNumber)
        {
            picSlaveCommand.Write(0x20);
        }
    }

    return esp;
}

InterruptHandler::InterruptHandler(uint8_t interruptNumber, InterruptManager &interruptManager)
{
    this->interruptNumber = interruptNumber;
    this->interruptManager = &interruptManager;

    interruptManager.interruptHandlers[interruptNumber] = this;
}

uint32_t InterruptHandler::HandleInterrupt(uint32_t esp)
{
    return esp;
}

InterruptHandler::~InterruptHandler()
{
    if (interruptManager->interruptHandlers[interruptNumber] == this)
    {
        interruptManager->interruptHandlers[interruptNumber] = nullptr;
    }
}

InterruptHandler::InterruptHandler()
{
}

InterruptHandler::InterruptHandler(const InterruptHandler &interruptHandler)
{
    Memory::Copy(this, &interruptHandler, sizeof(interruptHandler));
}