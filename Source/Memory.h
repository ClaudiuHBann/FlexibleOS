/*+===================================================================
  File:      Memory.h

  Summary:   Basic memory operations.

  Classes:   Memory

  Copyright and Legal notices.
===================================================================+*/

#ifndef _MEMORY_H
#define _MEMORY_H

#include "Types.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Memory

  Summary:  Basic memory operations.

  Methods:  Copy
              Copies the n long memory from an address to another address.
            Set
              Sets the n long memory from an address with a specific value.

            Memory
              Default/Copy constructor.
            ~Memory
              Default destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class Memory
{
public:
    Memory();
    Memory(const Memory &memory);
    ~Memory();

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Memory::Set

      Summary:  Sets the length of destination with a specific value.

      Args:     void* destination
                  Where to set.
                int32_t value
                  With what value to set.
                uint64_t length
                  How much to set.

      Returns:  void*
                  Returns the destination.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static void* Set(void *destination, int32_t value, uint64_t length);

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   Memory::Copy

      Summary:  Copies the length of source to destination.

      Args:     void* destination
                  Where to copy.
                void* source
                  From where to copy.
                uint64_t length
                  How much to copy.

      Returns:  void*
                  Returns the destination.
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    static void* Copy(void *destination, const void *source, uint64_t length);
};

#endif // !_MEMORY_H