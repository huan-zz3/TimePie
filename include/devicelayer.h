#ifndef DEVICELAYER_H
#define DEVICELAYER_H

#include "predefine.h"
#include "iepd_driver.h"

class DeviceLayer : public IEPD_Driver
{
public:
    void epdriver_Delay(Result<void>, uint32_t);
    void epdriver_ReadPin(Result<PinVal>, PinNum);
    void epdriver_WritePin(Result<void>, PinNum, PinVal);

    void epdriver_Init(Result<void>, InitMode);
    void epdriver_Clear(Result<void>, ClearMode);
    void epdriver_Display(Result<void>, ImageBuffer, DisplayMode);
    void epdriver_Sleep(Result<void>);

    void epdriver_NewImage(Result<void>, ImageBuffer, ImageColor);
    void epdriver_SetRotate(Result<void>, ImageBuffer, RotateMode);
    void epdriver_SetMirroring(Result<void>, ImageBuffer, MirrorMode);

    void epdriver_Clear(Result<void>, ImageBuffer, ImageColor);
    void epdriver_Clear(Result<void>, ImageBuffer, ImageColor, PointCoordinates, PointCoordinates);

    void epdriver_DrawPoint(Result<void>, ImageBuffer, PointCoordinates, ImageColor, PointSize, PointStyle);
    void epdriver_DrawLine(Result<void>, ImageBuffer, PointCoordinates, PointCoordinates, ImageColor, PointSize, LineStyle);
    void epdriver_DrawRectangle(Result<void>, ImageBuffer, PointCoordinates, PointCoordinates, ImageColor, PointSize, DrawFill);
    void epdriver_DrawCircle(Result<void>, ImageBuffer, PointCoordinates, RaiusLength, ImageColor, PointSize, DrawFill);

    void epdriver_DrawChar(Result<void>, ImageBuffer, PointCoordinates, char, Fontype, ImageColor, ImageColor);
    void epdriver_DrawString_EN(Result<void>, ImageBuffer, PointCoordinates, std::string, Fontype, ImageColor, ImageColor);
    void epdriver_DrawNum(Result<void>, ImageBuffer, PointCoordinates, Number, Fontype, ImageColor, ImageColor);
    void epdriver_DrawTime(Result<void>, ImageBuffer, PointCoordinates, Time, Fontype, ImageColor, ImageColor);
    void epdriver_DrawDate(Result<void>, ImageBuffer, PointCoordinates, Time, Fontype, ImageColor, ImageColor);

    void epdriver_ReadBmp(Result<void>, ImageBuffer, std::string, PointCoordinates);
};

#endif