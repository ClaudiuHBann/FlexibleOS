#ifndef _TYPES_H
#define _TYPES_H

typedef void (*Constructor)();

typedef char                    int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long int           int64_t;

typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long int  uint64_t;

typedef struct _MULTIBOOT_INFO
{
    uint32_t magic;       //all required...
    uint32_t flags;
    uint32_t checksum;
    uint32_t headerAddr;  //all optional, set if bit 16 in flags is set...
    uint32_t loadAddr;
    uint32_t loadEndAddr;
    uint32_t bssEndAddr;
    uint32_t entryPoint;
    uint32_t modType;     //all optional, set if bit 2 in flags is set...
    uint32_t width;
    uint32_t height;
    uint32_t depth;

}MULTIBOOT_INFO, *PMULTIBOOT_INFO;

#endif // !_TYPES_H