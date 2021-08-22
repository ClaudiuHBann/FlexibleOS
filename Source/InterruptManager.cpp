#include "InterruptManager.h"

InterruptManager::gateDescriptor_s InterruptManager::s_interruptDescriptorTable[256];

InterruptManager::InterruptManager()
{

}

InterruptManager::InterruptManager(const InterruptManager &interruptManager)
{
    Memory::Copy(this, &interruptManager, sizeof(interruptManager));
}

void InterruptManager::Activate()
{
    asm("sti");
}

InterruptManager::InterruptManager(GlobalDescriptorTable& globalDescriptorTable)
:picMasterCommand(0x20),
picMasterData(0x21),
picSlaveCommand(0xA0),
picSlaveData(0xA1)
{
    uint16_t codeSegment = globalDescriptorTable.GetCodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for (uint16_t i = 0; i < 256; i++)
    {
        SetInterruptDescriptorTableEntry(i, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }
    
    SetInterruptDescriptorTableEntry(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    
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

    asm volatile("lidt %0": :"m" (interruptDescriptorTable));
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
    Console::Write("INTERRUPT");

    return esp;
}