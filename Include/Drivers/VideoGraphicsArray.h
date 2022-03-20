#ifndef _VIDEOGRAPHICSARRAY_H
#define _VIDEOGRAPHICSARRAY_H

#include <HardwareCommunication/Port.h>

#include <Common/Types.h>

#define VGA_MODE_TEXT_40x25 40, 25
#define VGA_MODE_TEXT_40x50 40, 50
#define VGA_MODE_TEXT_80x25 80, 25
#define VGA_MODE_TEXT_80x50 80, 50
#define VGA_MODE_TEXT_90x30 90, 30
#define VGA_MODE_TEXT_90x60 90, 60

#define VGA_MODE_GRAPHIC_640x480x2 640, 480, 2
#define VGA_MODE_GRAPHIC_320x200x4 320, 200, 4
#define VGA_MODE_GRAPHIC_640x480x16 640, 480, 16
#define VGA_MODE_GRAPHIC_720x480x16 720, 480, 16
#define VGA_MODE_GRAPHIC_320x200x256 320, 200, 256

class VideoGraphicsArray
{
public:
    VideoGraphicsArray();
    ~VideoGraphicsArray();

    virtual bool SupportsTextMode(uint32_t width, uint32_t height);
    virtual bool SupportsGraphicMode(uint32_t width, uint32_t height, uint32_t colordepth);

    virtual bool SetTextMode(uint32_t width, uint32_t height);
    virtual bool SetGraphicMode(uint32_t width, uint32_t height, uint32_t colordepth);

    virtual void PutPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
    virtual void PutPixel(uint32_t x, uint32_t y, uint8_t colorIndex);

    virtual void ClearScreen(uint8_t colorIndex = 0);

protected:
    Port8 miscPort;
    Port8 crtcIndexPort;
    Port8 crtcDataPort;
    Port8 sequencerIndexPort;
    Port8 sequencerDataPort;
    Port8 graphicsControllerIndexPort;
    Port8 graphicsControllerDataPort;
    Port8 attributeControllerIndexPort;
    Port8 attributeControllerReadPort;
    Port8 attributeControllerWritePort;
    Port8 attributeControllerResetPort;

    void WriteRegisters(uint8_t *registers);
    uint8_t *GetFrameBufferSegment();

    virtual uint8_t GetColorIndex(uint8_t r, uint8_t g, uint8_t b);

private:
    uint16_t m_sizeX = 0;
    uint16_t m_sizeY = 0;
};

#endif // !_VIDEOGRAPHICSARRAY_H