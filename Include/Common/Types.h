#ifndef _TYPES_H
#define _TYPES_H

#define INT8_MIN (-127 - 1)
#define INT16_MIN (-32767 - 1)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN (-9223372036854775807 - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807

#define UINT8_MAX 0xffu
#define UINT16_MAX 0xffffu
#define UINT32_MAX 0xffffffffu
#define UINT64_MAX 0xffffffffffffffffu

#define KILOBYTE 1024
#define MEGABYTE (1024 * 1024)
#define GIGABYTE (1024 * MEGABYTE)

typedef void (*constructor_t)();

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef char *int8ptr_t;
typedef short *int16ptr_t;
typedef int *int32ptr_t;
typedef long long *int64ptr_t;

typedef unsigned char *uint8ptr_t;
typedef unsigned short *uint16ptr_t;
typedef unsigned int *uint32ptr_t;
typedef unsigned long long *uint64ptr_t;

typedef struct multibootHeader_s
{
    uint32_t m_magic;
    uint32_t m_flags;
    uint32_t m_checksum;
    uint32_t m_header_addr;
    uint32_t m_load_addr;
    uint32_t m_load_end_addr;
    uint32_t m_bss_end_addr;
    uint32_t m_entry_addr;
    uint32_t m_mode_type;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_depth;
} multibootHeader_t, *pMultibootHeader_t;

typedef struct coordinates_s
{
    uint8_t m_x;
    uint8_t m_y;
} coordinates_t, *pCoordinates_t;

typedef struct size_s
{
    uint8_t m_width;
    uint8_t m_height;
} size_t, *pSize_t;

typedef struct rectangle_s
{
    uint8_t m_x;
    uint8_t m_y;
    uint8_t m_width;
    uint8_t m_height;
} rectangle_t, *pRectangle_t;

#endif // !_TYPES_H