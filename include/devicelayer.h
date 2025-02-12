#ifndef DEVICELAYER_H
#define DEVICELAYER_H

#include "predefine.h"
#include "iepd_driver.h"

class DeviceLayer : public IEPD_Driver
{
public:
    Result<void> epdriver_Delay(uint32_t);
    Result<PinVal> epdriver_ReadPin(PinNum);
    Result<void> epdriver_WritePin(PinNum, PinVal);

    Result<void> epdriver_Init(InitMode);
    Result<void> epdriver_Clear(ClearMode);
    Result<void> epdriver_Display(ImageBuffer, DisplayMode);
    Result<void> epdriver_Sleep();
    Result<void> epdriver_Exit();

    Result<void> epdriver_NewImage(ImageBuffer, ImageColor);
    Result<void> epdriver_SetRotate(ImageBuffer, RotateMode);
    Result<void> epdriver_SetMirroring(ImageBuffer, MirrorMode);

    Result<void> epdriver_Clear(ImageBuffer, ImageColor);
    Result<void> epdriver_Clear(ImageBuffer, ImageColor, PointCoordinates, PointCoordinates);

    Result<void> epdriver_DrawPoint(ImageBuffer, PointCoordinates, ImageColor, PointSize, PointStyle);
    Result<void> epdriver_DrawLine(ImageBuffer, PointCoordinates, PointCoordinates, ImageColor, PointSize, LineStyle);
    Result<void> epdriver_DrawRectangle(ImageBuffer, PointCoordinates, PointCoordinates, ImageColor, PointSize, DrawFill);
    Result<void> epdriver_DrawCircle(ImageBuffer, PointCoordinates, RaiusLength, ImageColor, PointSize, DrawFill);

    Result<void> epdriver_DrawChar(ImageBuffer, PointCoordinates, char, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawString_EN(ImageBuffer, PointCoordinates, std::string, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawNum(ImageBuffer, PointCoordinates, Number, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawTime(ImageBuffer, PointCoordinates, Time, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawDate(ImageBuffer, PointCoordinates, Time, Fontype, ImageColor, ImageColor);

    Result<void> epdriver_ReadBmp(ImageBuffer, std::string, PointCoordinates);
};

#endif