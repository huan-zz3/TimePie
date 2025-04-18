#ifndef DEVICELAYER_H
#define DEVICELAYER_H

#include <result.hpp>
#include <predefine.h>
#include <chrono>

#include <memory>

extern "C" {
#include "EPD_2in13_V4.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "fonts.h"
#include "GT1151.h"
extern int IIC_Address;
extern GT1151_Dev Dev_Now, Dev_Old;
extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;
}

enum class InitMode
{
    Hardware,
    Full,
    Part,
    Fast
};

typedef UWORD PinNum;
typedef UBYTE PinVal;
enum class ClearMode
{
    White,
    Black
};
enum class DisplayMode
{
    Normal,
    Fast,
    Base,
    Partial,
    Partial_Wait
};
enum class ImageColor
{
    White = WHITE,
    Black = BLACK,
    Red = Black
};
enum class RotateMode
{
    Rotate_0 = 0,
    Rotate_90 = ROTATE_90,
    Rotate_180 = ROTATE_180,
    Rotate_270 = ROTATE_270
};
enum class MirrorMode
{
    None = MIRROR_NONE,
    Horizontal = MIRROR_HORIZONTAL,
    Vertical = MIRROR_VERTICAL,
    Origin = MIRROR_ORIGIN
};

struct ImageBuffer_struct
{
    PAINT *imgbuff_ptr;
    PAINT imgbuff;
};
typedef std::shared_ptr<ImageBuffer_struct> ImageBuffer_ptr;

enum class ScaleMode
{
    Double,
    Fourfold,
    Sevenfold
};

struct PointCoordinates
{
    UWORD x;
    UWORD y;
};

struct Dimensions
{
    UWORD w;
    UWORD h;
};

enum class PointSize
{
    X11 = DOT_PIXEL_1X1,
    X22 = DOT_PIXEL_2X2,
    X33 = DOT_PIXEL_3X3,
    X44 = DOT_PIXEL_4X4,
    X55 = DOT_PIXEL_5X5,
    X66 = DOT_PIXEL_6X6,
    X77 = DOT_PIXEL_7X7,
    X88 = DOT_PIXEL_8X8
};

enum class PointStyle
{
    Center = DOT_FILL_AROUND,
    UpperLeft = DOT_FILL_RIGHTUP
};

enum class LineStyle
{
    Solid = LINE_STYLE_SOLID,
    Dotted = LINE_STYLE_DOTTED
};

enum class DrawFill
{
    Fill = DRAW_FILL_FULL,
    NoFill = DRAW_FILL_EMPTY
};

typedef UWORD RaiusLength;

#define Fontype sFONT *
#define Font8 &Font8
#define Font12 &Font12
#define Font16 &Font16
#define Font20 &Font20
#define Font24 &Font24

typedef int32_t Number;

// struct Time{
//     UWORD Year;  //0000
//     UBYTE  Month; //1 - 12
//     UBYTE  Day;   //1 - 30
//     UBYTE  Hour;  //0 - 23
//     UBYTE  Min;   //0 - 59
//     UBYTE  Sec;   //0 - 59
// };
typedef PAINT_TIME Time;

typedef sigc::signal<void, PointCoordinates>    Signal_coordinate;
typedef sigc::slot<void, PointCoordinates>      Slot_coordinate;

class DeviceLayer
{
public:
    Result<void> epdriver_Delay(uint32_t);
    Result<PinVal> epdriver_ReadPin(PinNum);
    Result<void> epdriver_WritePin(PinNum, PinVal);

    Result<void> epdriver_Init(InitMode);
    Result<void> epdriver_Clear(ClearMode);
    Result<void> epdriver_Display(ImageBuffer_ptr, DisplayMode);
    Result<void> epdriver_Sleep();
    Result<void> epdriver_Exit();

    Result<ImageBuffer_ptr> epdriver_NewImage(ImageColor);
    Result<void> epdriver_SetRotate(ImageBuffer_ptr, RotateMode);
    Result<void> epdriver_SetMirroring(ImageBuffer_ptr, MirrorMode);

    Result<void> epdriver_imgClear(ImageBuffer_ptr, ImageColor);
    Result<void> epdriver_imgClear(ImageBuffer_ptr, ImageColor, PointCoordinates, PointCoordinates);

    Result<void> epdriver_DrawPoint(ImageBuffer_ptr, PointCoordinates, ImageColor, PointSize, PointStyle);
    Result<void> epdriver_DrawLine(ImageBuffer_ptr, PointCoordinates, PointCoordinates, ImageColor, PointSize, LineStyle);
    Result<void> epdriver_DrawRectangle(ImageBuffer_ptr, PointCoordinates, PointCoordinates, ImageColor, PointSize, DrawFill);
    Result<void> epdriver_DrawCircle(ImageBuffer_ptr, PointCoordinates, RaiusLength, ImageColor, PointSize, DrawFill);

    Result<void> epdriver_DrawChar(ImageBuffer_ptr, PointCoordinates, char, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawString_EN(ImageBuffer_ptr, PointCoordinates, std::string, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawNum(ImageBuffer_ptr, PointCoordinates, Number, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawTime(ImageBuffer_ptr, PointCoordinates, Time, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawDate(ImageBuffer_ptr, PointCoordinates, Time, Fontype, ImageColor, ImageColor);

    Result<Dimensions> epdriver_GetDrawRange(std::string, PointCoordinates, Fontype);

    Result<void> epdriver_ReadBmp(ImageBuffer_ptr, std::string, PointCoordinates);

    Result<void> epdriver_TouchInit(void);
    Result<PointCoordinates> epdriver_TouchScan(void);

private:
    std::chrono::steady_clock::time_point lastTouchTime = std::chrono::steady_clock::now();
    

};

#endif