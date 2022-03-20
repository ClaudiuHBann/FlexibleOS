#ifndef _MISCELLANEOUS_H
#define _MISCELLANEOUS_H

#include <HardwareCommunication/Port.h>

#include <Common/Types.h>

#define CURRENT_YEAR 2022

typedef struct SystemTime
{
    uint8_t seconds, minutes, hours;
} SystemTime;

typedef struct SystemDate
{
    uint8_t days, months;
    uint32_t years;
} SystemDate;

typedef struct SystemDateTime
{
    SystemTime time;
    SystemDate date;
} SystemDateTime;

class Miscellaneous
{
public:
    Miscellaneous();
    ~Miscellaneous();

    static void SoundPlay(uint32_t frequency);
    static void SoundStop();
    static void SoundBeep();

    static SystemDateTime BCDToBinary(SystemDateTime &sdt)
    {
        uint8_t registerB = GetRTCRegister(0x0B);

        if (!(registerB & 0x04))
        {
            sdt.time.seconds = (sdt.time.seconds & 0x0F) + (sdt.time.seconds / 16) * 10;
            sdt.time.minutes = (sdt.time.minutes & 0x0F) + (sdt.time.minutes / 16) * 10;
            sdt.time.hours = ((sdt.time.hours & 0x0F) + (((sdt.time.hours & 0x70) / 16) * 10)) | (sdt.time.hours & 0x80);
            sdt.date.days = (sdt.date.days & 0x0F) + (sdt.date.days / 16) * 10;
            sdt.date.months = (sdt.date.months & 0x0F) + (sdt.date.months / 16) * 10;
            sdt.date.years = (sdt.date.years & 0x0F) + (sdt.date.years / 16) * 10;
        }

        if (!(registerB & 0x02) && (sdt.time.hours & 0x80))
        {
            sdt.time.hours = ((sdt.time.hours & 0x7F) + 12) % 24;
        }

        sdt.date.years += (CURRENT_YEAR / 100) * 100;
        if (sdt.date.years < CURRENT_YEAR)
        {
            sdt.date.years += 100;
        }

        return sdt;
    }

    static SystemDateTime ReadRTC()
    {
        SystemDateTime lastSDT;

        while (GetUpdateInProgressFlag())
            ;

        SystemDateTime sdt = {GetRTCRegister(0x00), GetRTCRegister(0x02), GetRTCRegister(0x04),
                              GetRTCRegister(0x07), GetRTCRegister(0x08), GetRTCRegister(0x09)};

        do
        {
            lastSDT = sdt;

            while (GetUpdateInProgressFlag())
                ;

            sdt = {GetRTCRegister(0x00), GetRTCRegister(0x02), GetRTCRegister(0x04),
                   GetRTCRegister(0x07), GetRTCRegister(0x08), GetRTCRegister(0x09)};
        } while ((lastSDT.time.seconds != sdt.time.seconds) || (lastSDT.time.minutes != sdt.time.minutes) || (lastSDT.time.hours != sdt.time.hours) ||
                 (lastSDT.date.days != sdt.date.days) || (lastSDT.date.months != sdt.date.months) || (lastSDT.date.years != sdt.date.years));

        return sdt;
    }

    static SystemDateTime ReadRTCAndConvert()
    {
        SystemDateTime sdt = ReadRTC();
        BCDToBinary(sdt);
        return sdt;
    }

private:
    static int32_t GetUpdateInProgressFlag();
    static uint8_t GetRTCRegister(int32_t reg);
};

#endif // !_MISCELLANEOUS_H