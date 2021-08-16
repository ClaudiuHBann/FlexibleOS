#ifndef _GLOBAL_DESCRIPTOR_TABLE_H
#define _GLOBAL_DESCRIPTOR_TABLE_H

#include "Types.h"
#include "Memory.h"

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
        uint16_t limitLowBytes;
        uint16_t baseLowBytesPointer;
        uint8_t baseHighBytesPointer;
        uint8_t accessRights;
        uint8_t flagsLimitHigh;
        uint8_t baseVhi;
    } __attribute__((packed));

    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;
};

#endif // !_GLOBAL_DESCRIPTOR_TABLE_H