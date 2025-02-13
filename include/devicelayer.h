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
    Result<void> epdriver_Display(ImageBuffer_ptr, DisplayMode);
    Result<void> epdriver_Sleep();
    Result<void> epdriver_Exit();

    Result<ImageBuffer_ptr> epdriver_NewImage(ImageColor);
    Result<void> epdriver_SetRotate(ImageBuffer_ptr, RotateMode);
    Result<void> epdriver_SetMirroring(ImageBuffer_ptr, MirrorMode);

    Result<void> epdriver_Clear(ImageBuffer_ptr, ImageColor);
    Result<void> epdriver_Clear(ImageBuffer_ptr, ImageColor, PointCoordinates, PointCoordinates);

    Result<void> epdriver_DrawPoint(ImageBuffer_ptr, PointCoordinates, ImageColor, PointSize, PointStyle);
    Result<void> epdriver_DrawLine(ImageBuffer_ptr, PointCoordinates, PointCoordinates, ImageColor, PointSize, LineStyle);
    Result<void> epdriver_DrawRectangle(ImageBuffer_ptr, PointCoordinates, PointCoordinates, ImageColor, PointSize, DrawFill);
    Result<void> epdriver_DrawCircle(ImageBuffer_ptr, PointCoordinates, RaiusLength, ImageColor, PointSize, DrawFill);

    Result<void> epdriver_DrawChar(ImageBuffer_ptr, PointCoordinates, char, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawString_EN(ImageBuffer_ptr, PointCoordinates, std::string, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawNum(ImageBuffer_ptr, PointCoordinates, Number, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawTime(ImageBuffer_ptr, PointCoordinates, Time, Fontype, ImageColor, ImageColor);
    Result<void> epdriver_DrawDate(ImageBuffer_ptr, PointCoordinates, Time, Fontype, ImageColor, ImageColor);

    Result<void> epdriver_ReadBmp(ImageBuffer_ptr, std::string, PointCoordinates);
};

#endif