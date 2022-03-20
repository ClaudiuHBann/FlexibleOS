#ifndef _GLOBAL_DESCRIPTOR_TABLE_H
#define _GLOBAL_DESCRIPTOR_TABLE_H

#include <Common/Memory.h>
#include <Common/Types.h>

class GlobalDescriptorTable
{
public:
    GlobalDescriptorTable();
    GlobalDescriptorTable(const GlobalDescriptorTable &globalDescriptorTable);
    ~GlobalDescriptorTable();

    uint16_t GetCodeSegmentSelector() const;
    uint16_t GetDataSegmentSelector() const;

    class SegmentDescriptor
    {
    public:
        SegmentDescriptor();
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        SegmentDescriptor(const SegmentDescriptor &segmentDescriptor);
        ~SegmentDescriptor();

        uint32_t GetBase() const;
        uint32_t GetLimit() const;

    private:
        uint16_t m_limitLowBytes;
        uint16_t m_baseLowBytes;
        uint8_t m_baseHighBytes;
        uint8_t m_type;
        uint8_t m_limitHighBytes;
        uint8_t m_baseVhi;
    } __attribute__((packed));

    SegmentDescriptor m_nullSegmentSelector;
    SegmentDescriptor m_unusedSegmentSelector;
    SegmentDescriptor m_codeSegmentSelector;
    SegmentDescriptor m_dataSegmentSelector;
};

#endif // !_GLOBAL_DESCRIPTOR_TABLE_H