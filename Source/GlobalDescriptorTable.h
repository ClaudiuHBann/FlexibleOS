/*+===================================================================
  File:      GlobalDescriptorTable.h

  Summary:   A data structure used by Intel x86-family processors.

  Classes:   GlobalDescriptorTable, SegmentDescriptor.

  Copyright and Legal notices.
===================================================================+*/

#ifndef _GLOBAL_DESCRIPTOR_TABLE_H
#define _GLOBAL_DESCRIPTOR_TABLE_H

#include "Types.h"
#include "Memory.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    GlobalDescriptorTable

  Summary:  A data structure used by Intel x86-family processors.

  Methods:  GetCodeSegmentSelector
              Retrieves the code segment selector.
            GetDataSegmentSelector
              Retrieves the data segment selector.

            GlobalDescriptorTable
              Default/Copy constructor.
            ~GlobalDescriptorTable
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class GlobalDescriptorTable
{
public:
    GlobalDescriptorTable();
    GlobalDescriptorTable(const GlobalDescriptorTable &globalDescriptorTable);
    ~GlobalDescriptorTable();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   GlobalDescriptorTable::GetCodeSegmentSelector

      Summary:  Retrieves the code segment selector.

      Returns:  uint16_t
                  The code segment selector.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    uint16_t GetCodeSegmentSelector() const;

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   GlobalDescriptorTable::GetDataSegmentSelector

      Summary:  Retrieves the data segment selector.

      Returns:  uint16_t
                  The data segment selector.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    uint16_t GetDataSegmentSelector() const;

    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    SegmentDescriptor

      Summary:  A part of the segmentation unit.

      Methods:  GetBase
                  Retrieves segment descriptor base.
                GetLimit
                  Retrieves segment descriptor limit.

                SegmentDescriptor
                  Default/Copy constructor.
                SegmentDescriptor
                  Initializes the base, limit and type.
                ~SegmentDescriptor
                  Default destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class SegmentDescriptor
    {
    public:
        SegmentDescriptor();
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        SegmentDescriptor(const SegmentDescriptor &segmentDescriptor);
        ~SegmentDescriptor();

        /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
          Method:   SegmentDescriptor::GetBase

          Summary:  Retrieves the segment descriptor base.

          Returns:  uint32_t
                      The segment descriptor base.
        M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
        uint32_t GetBase() const;

        /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
          Method:   SegmentDescriptor::GetLimit

          Summary:  Retrieves the segment descriptor limit.

          Returns:  uint32_t
                      The segment descriptor limit.
        M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
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