#ifndef _EVERYTHING_H
#define _EVERYTHING_H

typedef void (*Constructor)();

typedef char                    int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long int           int64_t;

typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long int  uint64_t;

typedef struct multiboot_info
{
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t headerAddr;
    uint32_t loadAddr;
    uint32_t loadEndAddr;
    uint32_t bssEndAddr;
    uint32_t entryPoint;
    uint32_t modType;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
}MultibootInfo;

class Console
{
public:
    static void Print(const int8_t* string);
    static void Print(int64_t integer);

private:
    static uint16_t* videoMemoryAddressStart, *lastVideoMemoryAddressPosition, *videoMemoryAddressEnd;
};

class Math
{
public:
    static int64_t Mod(int64_t num, int64_t divisor);
    static int64_t Absolute(int64_t integer);
    static int64_t Divide(int64_t dividend, int64_t divisor);
};

class Converter
{
public:
    static const char* IntegerToString(int64_t integer);
    static int64_t StringToInteger(const int8_t* string);
    static const int8_t* Base10ToAnyBase(int64_t value, const uint8_t base);
};

class Memory
{
public:
    static void* MemorySet(void *destination, int32_t value, uint64_t length);
    static void* MemoryCopy(void *destination, const void *source, uint64_t length);
};

#endif // !_EVERYTHING_H