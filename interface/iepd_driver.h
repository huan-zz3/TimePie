#ifndef IEPD_DRIVER_H
#define IEPD_DRIVER_H

#include "predefine.h"
#include <memory>

#include "EPD_2in13_V4.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "fonts.h"

enum class InitMode
{
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
    UBYTE *imgbuff_ptr;
};
typedef std::shared_ptr<ImageBuffer_struct> ImageBuffer;

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

enum class PointSize
{
    X11 = DOT_PIXEL_1X1,
    X11 = DOT_PIXEL_2X2,
    X33 = DOT_PIXEL_3X3,
    X44 = DOT_PIXEL_4X4,
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

extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;
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

class IEPD_Driver
{
public:
    explicit IEPD_Driver();

    /* Some encapsulations-func of Waveshare IEPD driver, after I know well about it. */
    /*
     * Encapsulations-func from DEV_Config.h
     */
    virtual void epdriver_Delay(Result<void>, uint32_t) = 0;
    virtual void epdriver_ReadPin(Result<PinVal>, PinNum) = 0;
    virtual void epdriver_WritePin(Result<void>, PinNum, PinVal) = 0;

    /*
     * Encapsulations-func from EPD_2in13_V4.h
     */
    virtual void epdriver_Init(Result<void>, InitMode) = 0;
    virtual void epdriver_Clear(Result<void>, ClearMode) = 0;
    virtual void epdriver_Display(Result<void>, ImageBuffer, DisplayMode) = 0;
    virtual void epdriver_Sleep(Result<void>) = 0;

    /*
     * Encapsulations-func from GUI_Paint.h
     */
    virtual void epdriver_NewImage(Result<void>, ImageBuffer, ImageColor) = 0;
    // virtual void epdriverSelect(Result<void>, ImageBuffer) = 0;
    virtual void epdriver_SetRotate(Result<void>, ImageBuffer, RotateMode) = 0;
    virtual void epdriver_SetMirroring(Result<void>, ImageBuffer, MirrorMode) = 0;
    // virtual void epdriverSetScale(Result<void>, ScaleMode) = 0;

    virtual void epdriver_Clear(Result<void>, ImageBuffer, ImageColor) = 0;
    virtual void epdriver_Clear(Result<void>, ImageBuffer, ImageColor, PointCoordinates, PointCoordinates) = 0;

    virtual void epdriver_DrawPoint(Result<void>, ImageBuffer, PointCoordinates, ImageColor, PointSize, PointStyle) = 0;
    virtual void epdriver_DrawLine(Result<void>, ImageBuffer, PointCoordinates, PointCoordinates, ImageColor, PointSize, LineStyle) = 0;
    virtual void epdriver_DrawRectangle(Result<void>, ImageBuffer, PointCoordinates, PointCoordinates, ImageColor, PointSize, DrawFill) = 0;
    virtual void epdriver_DrawCircle(Result<void>, ImageBuffer, PointCoordinates, RaiusLength, ImageColor, PointSize, DrawFill) = 0;

    virtual void epdriver_DrawChar(Result<void>, ImageBuffer, PointCoordinates, char, Fontype, ImageColor, ImageColor) = 0;
    virtual void epdriver_DrawString_EN(Result<void>, ImageBuffer, PointCoordinates, std::string, Fontype, ImageColor, ImageColor) = 0;
    virtual void epdriver_DrawNum(Result<void>, ImageBuffer, PointCoordinates, Number, Fontype, ImageColor, ImageColor) = 0;
    virtual void epdriver_DrawTime(Result<void>, ImageBuffer, PointCoordinates, Time, Fontype, ImageColor, ImageColor) = 0;
    virtual void epdriver_DrawDate(Result<void>, ImageBuffer, PointCoordinates, Time, Fontype, ImageColor, ImageColor) = 0;

    /*
     * Encapsulations-func from GUI_BMPfile.h
     */
    virtual void epdriver_ReadBmp(Result<void>, ImageBuffer, std::string, PointCoordinates) = 0;
};

#endif