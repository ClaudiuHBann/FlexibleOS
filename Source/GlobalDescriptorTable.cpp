#include <GlobalDescriptorTable.h>

GlobalDescriptorTable::GlobalDescriptorTable() : m_nullSegmentSelector(0, 0, 0),
                                                 m_unusedSegmentSelector(0, 0, 0),
                                                 m_codeSegmentSelector(0, 64 * MEGABYTE, 0x9A),
                                                 m_dataSegmentSelector(0, 64 * MEGABYTE, 0x92)
{
    uint32_t temporary[2];
    temporary[1] = (uint32_t)this;
    temporary[0] = sizeof(GlobalDescriptorTable) << 16;

    asm volatile("lgdt (%0)"
                 :
                 : "p"(((uint8_t *)temporary) + 2));
}

GlobalDescriptorTable::GlobalDescriptorTable(const GlobalDescriptorTable &globalDescriptorTable)
{
    Memory::Copy(this, &globalDescriptorTable, sizeof(globalDescriptorTable));
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16_t GlobalDescriptorTable::GetDataSegmentSelector() const
{
    return (uint8_t *)&m_dataSegmentSelector - (uint8_t *)this;
}

uint16_t GlobalDescriptorTable::GetCodeSegmentSelector() const
{
    return (uint8_t *)&m_codeSegmentSelector - (uint8_t *)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type)
{
    uint8_t *target = (uint8_t *)this;

    if (limit <= 65536)
    {
        target[6] = 0x40;
    }
    else
    {
        if ((limit & 0xFFF) != 0xFFF)
        {
            limit = (limit >> 12) - 1;
        }
        else
        {
            limit = limit >> 12;
        }

        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = type;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor()
{
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(const SegmentDescriptor &segmentDescriptor)
{
    Memory::Copy(this, &segmentDescriptor, sizeof(segmentDescriptor));
}

GlobalDescriptorTable::SegmentDescriptor::~SegmentDescriptor()
{
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::GetBase() const
{
    uint8_t *target = (uint8_t *)this;
    uint32_t result = target[7];

    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::GetLimit() const
{
    uint8_t *target = (uint8_t *)this;
    uint32_t result = target[6] & 0xF;

    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if ((target[6] & 0xC0) == 0xC0)
    {
        result = (result << 12) | 0xFFF;
    }

    return result;
}