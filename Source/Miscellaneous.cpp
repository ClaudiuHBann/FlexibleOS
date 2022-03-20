#include <Miscellaneous.h>

#define CMOS_PORT_ADDRESS 0x70
#define CMOS_PORT_DATA 0x71

Miscellaneous::Miscellaneous()
{
}

Miscellaneous::~Miscellaneous()
{
}

void Miscellaneous::SoundPlay(uint32_t frequency)
{
    uint32_t div = 1193180 / frequency;
    outb(0x43, 0xB6);
    outb(0x42, div);
    outb(0x42, div >> 8);

    uint8_t tmp = inb(0x61);
    if (tmp != (tmp | 3))
    {
        outb(0x61, tmp | 3);
    }
}

void Miscellaneous::SoundStop()
{
    outb(0x61, inb(0x61) & 0xFC);
}

void Miscellaneous::SoundBeep()
{
    SoundPlay(1000);
    SoundStop();
}

int32_t Miscellaneous::GetUpdateInProgressFlag()
{
    outb(CMOS_PORT_ADDRESS, 0x0A);
    return (inb(CMOS_PORT_DATA) & 0x80);
}

uint8_t Miscellaneous::GetRTCRegister(int32_t reg)
{
    outb(CMOS_PORT_ADDRESS, reg);
    return inb(CMOS_PORT_DATA);
}