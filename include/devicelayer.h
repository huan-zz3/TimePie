#ifndef DEVICELAYER_H
#define DEVICELAYER_H

#include "predefine.h"
#include "iepd_driver.h"

class DeviceLayer : public IEPD_Driver
{
public:
    Result<void> epdriver_Delay(uint32_t) override;
    Result<PinVal> epdriver_ReadPin(PinNum) override;
    Result<void> epdriver_WritePin(PinNum, PinVal) override;

    Result<void> epdriver_Init(InitMode) override;
    Result<void> epdriver_Clear(ClearMode) override;
    Result<void> epdriver_Display(ImageBuffer_ptr, DisplayMode) override;
    Result<void> epdriver_Sleep() override;
    Result<void> epdriver_Exit() override;

    Result<ImageBuffer_ptr> epdriver_NewImage(ImageColor) override;
    Result<void> epdriver_SetRotate(ImageBuffer_ptr, RotateMode) override;
    Result<void> epdriver_SetMirroring(ImageBuffer_ptr, MirrorMode) override;

    Result<void> epdriver_imgClear(ImageBuffer_ptr, ImageColor) override;
    Result<void> epdriver_imgClear(ImageBuffer_ptr, ImageColor, PointCoordinates, PointCoordinates) override;

    Result<void> epdriver_DrawPoint(ImageBuffer_ptr, PointCoordinates, ImageColor, PointSize, PointStyle) override;
    Result<void> epdriver_DrawLine(ImageBuffer_ptr, PointCoordinates, PointCoordinates, ImageColor, PointSize, LineStyle) override;
    Result<void> epdriver_DrawRectangle(ImageBuffer_ptr, PointCoordinates, PointCoordinates, ImageColor, PointSize, DrawFill) override;
    Result<void> epdriver_DrawCircle(ImageBuffer_ptr, PointCoordinates, RaiusLength, ImageColor, PointSize, DrawFill) override;

    Result<void> epdriver_DrawChar(ImageBuffer_ptr, PointCoordinates, char, Fontype, ImageColor, ImageColor) override;
    Result<void> epdriver_DrawString_EN(ImageBuffer_ptr, PointCoordinates, std::string, Fontype, ImageColor, ImageColor) override;
    Result<void> epdriver_DrawNum(ImageBuffer_ptr, PointCoordinates, Number, Fontype, ImageColor, ImageColor) override;
    Result<void> epdriver_DrawTime(ImageBuffer_ptr, PointCoordinates, Time, Fontype, ImageColor, ImageColor) override;
    Result<void> epdriver_DrawDate(ImageBuffer_ptr, PointCoordinates, Time, Fontype, ImageColor, ImageColor) override;

    Result<Dimensions> epdriver_GetDrawRange(std::string, PointCoordinates, Fontype) override;

    Result<void> epdriver_ReadBmp(ImageBuffer_ptr, std::string, PointCoordinates) override;

    Result<void> epdriver_TouchInit(void) override;
    Result<void> epdriver_TouchScan(void) override;
};

#endif