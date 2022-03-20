#include <Drivers/Mouse.h>

#define PS2MOUSE_INTELLIMOUSE_ID 3

void mouse_wait(uint8_t a_type)
{
    uint32_t _time_out = 100000; // unsigned int
    if (a_type == 0)
    {
        while (_time_out--)
        {
            if ((inportb(0x64) & 1) == 1)
            {
                return;
            }
        }
        return;
    }
    else
    {
        while (_time_out--)
        {
            if ((inportb(0x64) & 2) == 0)
            {
                return;
            }
        }
        return;
    }
}

void mouse_write(uint8_t a_write) // unsigned char
{
    // Tell the mouse we are sending a command
    mouse_wait(1);
    outportb(0x64, 0xD4);
    mouse_wait(1);
    // Finally write
    outportb(0x60, a_write);
}

uint8_t mouse_read()
{
    mouse_wait(0);
    return inportb(0x60);
}

MouseDriver::MouseDriver(InterruptManager &interruptManager) : InterruptHandler(0x2C, interruptManager),
                                                               dataPort(0x60),
                                                               commandPort(0x64)
{
    
}

void MouseDriver::Activate()
{
    static uint16_t *videoMemory = (uint16_t *)0xB8000;
    videoMemory[80 * 12 + 40] = ((videoMemory[80 * 12 + 40] & 0xF000) >> 4) |
                                ((videoMemory[80 * 12 + 40] & 0x0F00) << 4) |
                                (videoMemory[80 * 12 + 40] & 0x00FF);

    uint8_t _status; // unsigned char
    // Enable the auxiliary mouse device
    mouse_wait(1);
    outportb(0x64, 0xA8);

    // Enable the interrupts
    mouse_wait(1);
    outportb(0x64, 0x20);
    mouse_wait(0);
    _status = (inportb(0x60) | 2);
    mouse_wait(1);
    outportb(0x64, 0x60);
    mouse_wait(1);
    outportb(0x60, _status);

    // Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read(); // Acknowledge

    // Enable the mouse
    mouse_write(0xF4);
    mouse_read(); // Acknowledge
    uint8_t device_id = mouse_read();

    if (device_id != 3)
    {
        mouse_write(0xF3);
        mouse_read();
        mouse_write(200);
        mouse_read();
        mouse_write(0xF3);
        mouse_read();
        mouse_write(100);
        mouse_read();
        mouse_write(0xF3);
        mouse_read();
        mouse_write(80);
        mouse_read();

        mouse_write(0xF2);
        mouse_read();
        device_id = mouse_read();
    }

    if (device_id == PS2MOUSE_INTELLIMOUSE_ID)
    {
    }
    else
    {
    }

    mouse_write(0xF2);
    mouse_read();
}

MouseDriver::~MouseDriver()
{
}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandPort.Read();
    if (!(status & 0x20))
    {
        return esp;
    }

    switch (offset)
    {
    case 0:
        buffer[0] = mouse_read();
        offset++;
        break;
    case 1:
        buffer[1] = mouse_read();
        offset++;
        break;
    case 2:
        buffer[2] = mouse_read();
        offset++;
        break;
    case 3:
        buffer[3] = mouse_read();
        offset = 0;
        break;
    }

    if (offset == 0)
    {
        static int8_t x = 40, y = 12;
        static uint16_t *videoMemory = (uint16_t *)0xB8000;

        videoMemory[80 * y + x] = ((videoMemory[80 * y + x] & 0xF000) >> 4) |
                                  ((videoMemory[80 * y + x] & 0x0F00) << 4) |
                                  (videoMemory[80 * y + x] & 0x00FF);

        x += buffer[1];

        if (x < 0)
        {
            x = 0;
        }

        if (x >= 80)
        {
            x = 79;
        }

        y -= buffer[2];

        if (y < 0)
        {
            y = 0;
        }

        if (y >= 25)
        {
            y = 24;
        }

        videoMemory[80 * y + x] = ((videoMemory[80 * y + x] & 0xF000) >> 4) |
                                  ((videoMemory[80 * y + x] & 0x0F00) << 4) |
                                  (videoMemory[80 * y + x] & 0x00FF);

        for (uint8_t i = 0; i < 3; i++)
        {
            if ((buffer[0] & (0x01 << i)) != (buttons & (0x01 << i)))
            {
                videoMemory[80 * y + x] = ((videoMemory[80 * y + x] & 0xF000) >> 4) |
                                          ((videoMemory[80 * y + x] & 0x0F00) << 4) |
                                          (videoMemory[80 * y + x] & 0x00FF);
            }
        }

        buttons = buffer[0];

        mouseButtonsState[0] = buttons & 1;
        mouseButtonsState[1] = (buttons >> 1) & 1;
        mouseButtonsState[2] = (buttons >> 2) & 1;

        wheel = buffer[3];
    }

    return esp;
}