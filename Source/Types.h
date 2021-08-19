/*+===================================================================
  File:      Types.h

  Summary:   Definitions of different data types.

  Copyright and Legal notices.
===================================================================+*/

#ifndef _TYPES_H
#define _TYPES_H

#define INT8_MIN    (-127 - 1)
#define INT16_MIN   (-32767 - 1)
#define INT32_MIN   (-2147483647 - 1)
#define INT64_MIN   (-9223372036854775807 - 1)

#define INT8_MAX    127
#define INT16_MAX   32767
#define INT32_MAX   2147483647
#define INT64_MAX   9223372036854775807

#define UINT8_MAX   0xffu
#define UINT16_MAX  0xffffu
#define UINT32_MAX  0xffffffffu
#define UINT64_MAX  0xffffffffffffffffu

#define KILOBYTE    1024
#define MEGABYTE    (1024 * 1024)
#define GIGABYTE    (1024 * MEGABYTE)

typedef void (*constructor_t)();

typedef char        int8_t;
typedef short       int16_t;
typedef int         int32_t;
typedef long long   int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef char*       int8ptr_t;
typedef short*      int16ptr_t;
typedef int*        int32ptr_t;
typedef long long*  int64ptr_t;

typedef unsigned char*      uint8ptr_t;
typedef unsigned short*     uint16ptr_t;
typedef unsigned int*       uint32ptr_t;
typedef unsigned long long* uint64ptr_t;

typedef struct multibootInfo_s
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

}multibootInfo_t, *pMultibootInfo_t;

typedef struct coordinates_s
{
    uint8_t x;
    uint8_t y;
}coordinates_t, *pCoordinates_t;

typedef struct size_s
{
    uint8_t width;
    uint8_t height;
}size_t, *pSize_t;

typedef struct rectangle_s
{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
}rectangle_t, *pRectangle_t;

#endif // !_TYPES_H