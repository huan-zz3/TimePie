#include "devicelayer.h"

Result<void> DeviceLayer::epdriver_Delay(uint32_t _ms)
{
    DEV_Delay_ms(_ms);
    return Result<void>::Success();
}
Result<PinVal> DeviceLayer::epdriver_ReadPin(PinNum _pin)
{
    PinVal _val = DEV_Digital_Read(_pin);
    if (_val < 0)
    {
        return Result<PinVal>::Error(std::string("ReadPin failed: %d", _val));
    }
    return Result<PinVal>::Success(_val);
}
Result<void> DeviceLayer::epdriver_WritePin(PinNum _pin, PinVal _val)
{
    DEV_Digital_Write(_pin, _val);
    return Result<void>::Success();
}

Result<void> DeviceLayer::epdriver_Init(InitMode _initMode)
{
    switch (_initMode)
    {
    case InitMode::Hardware:
        IIC_Address = 0x14;
        if (DEV_ModuleInit())
        {
            LOG(ERROR) << "DEV_ModuleInit Failed!" << std::endl;
            return Result<void>::Error("DEV_ModuleInit Failed!");
        }
        break;
    case InitMode::Full:
        EPD_2in13_V4_Init(EPD_2IN13_V4_FULL);
        break;
    case InitMode::Part:
        EPD_2in13_V4_Init(EPD_2IN13_V4_PART);
        break;
    case InitMode::Fast:
        EPD_2in13_V4_Init(EPD_2IN13_V4_Fast);
        break;
    }
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_Exit()
{
    DEV_ModuleExit();
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_Clear(ClearMode _clearmode)
{
    switch (_clearmode)
    {
    case ClearMode::White:
        EPD_2in13_V4_Clear();
        break;
    case ClearMode::Black:
        EPD_2in13_V4_Clear_Black();
        break;
    }
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_Display(ImageBuffer_ptr _imagebuffer, DisplayMode _displaymode)
{
    switch (_displaymode)
    {
    case DisplayMode::Normal:
        EPD_2in13_V4_Display(_imagebuffer->imgbuff_ptr->Image);
        break;
    case DisplayMode::Fast:
        EPD_2in13_V4_Display_Fast(_imagebuffer->imgbuff_ptr->Image);
        break;
    case DisplayMode::Base:
        EPD_2in13_V4_Display_Base(_imagebuffer->imgbuff_ptr->Image);
        break;
    case DisplayMode::Partial:
        EPD_2in13_V4_Display_Partial(_imagebuffer->imgbuff_ptr->Image);
        break;
    case DisplayMode::Partial_Wait:
        EPD_2in13_V4_Display_Partial_Wait(_imagebuffer->imgbuff_ptr->Image);
        break;
    }
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_Sleep()
{
    EPD_2in13_V4_Sleep();
    return Result<void>::Success();
}

Result<ImageBuffer_ptr> DeviceLayer::epdriver_NewImage(ImageColor _imagecolor)
{
    ImageBuffer_ptr _imagebuffer = std::make_shared<ImageBuffer_struct>();
    _imagebuffer->imgbuff_ptr = &_imagebuffer->imgbuff;
    _imagebuffer->imgbuff_ptr->Image = (UBYTE *)malloc((EPD_2in13_V4_WIDTH / 8 + 1) * EPD_2in13_V4_HEIGHT); // the imagesize is fixed in EPD_2in13_V4: (EPD_2in13_V4_WIDTH / 8 + 1) * EPD_2in13_V4_HEIGHT
    switch (_imagecolor)
    {
    case ImageColor::White:
        Paint_NewImage(_imagebuffer->imgbuff_ptr, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 0, WHITE);
        epdriver_imgClear(_imagebuffer, _imagecolor);
        break;
    case ImageColor::Black:
        Paint_NewImage(_imagebuffer->imgbuff_ptr, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 0, BLACK);
        epdriver_imgClear(_imagebuffer, _imagecolor);
        break;
    }
    return Result<ImageBuffer_ptr>::Success(_imagebuffer);
}
Result<void> DeviceLayer::epdriver_SetRotate(ImageBuffer_ptr _imagebuffer, RotateMode _rotatemode)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_SetRotate(static_cast<UWORD>(_rotatemode));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_SetMirroring(ImageBuffer_ptr _imagebuffer, MirrorMode _mirrormode)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_SetMirroring(static_cast<UWORD>(_mirrormode));
    return Result<void>::Success();
}

Result<void> DeviceLayer::epdriver_imgClear(ImageBuffer_ptr _imagebuffer, ImageColor _imagecolor)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_Clear(static_cast<UWORD>(_imagecolor));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_imgClear(ImageBuffer_ptr _imagebuffer, ImageColor _imagecolor, PointCoordinates _pcs, PointCoordinates _pce)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_ClearWindows(_pcs.x, _pcs.y, _pce.x, _pce.y, static_cast<UWORD>(_imagecolor));
    return Result<void>::Success();
}

Result<void> DeviceLayer::epdriver_DrawPoint(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, ImageColor _imagecolor, PointSize _pointsize, PointStyle _pointstyle)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawPoint(_pc.x, _pc.y, static_cast<UWORD>(_imagecolor), static_cast<DOT_PIXEL>(_pointsize), static_cast<DOT_STYLE>(_pointstyle));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawLine(ImageBuffer_ptr _imagebuffer, PointCoordinates _pcs, PointCoordinates _pce, ImageColor _imagecolor, PointSize _pointsize, LineStyle _linestyle)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawLine(_pcs.x, _pcs.y, _pce.x, _pce.y, static_cast<UWORD>(_imagecolor), static_cast<DOT_PIXEL>(_pointsize), static_cast<LINE_STYLE>(_linestyle));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawRectangle(ImageBuffer_ptr _imagebuffer, PointCoordinates _pcx, PointCoordinates _pcy, ImageColor _imagecolor, PointSize _pointsize, DrawFill _drawfill)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawRectangle(_pcx.x, _pcx.y, _pcy.x, _pcy.y, static_cast<UWORD>(_imagecolor), static_cast<DOT_PIXEL>(_pointsize), static_cast<DRAW_FILL>(_drawfill));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawCircle(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, RaiusLength _radius, ImageColor _imagecolor, PointSize _pointsize, DrawFill _drawfill)
{
    // LOG(INFO)("DeviceLayer::epdriver_DrawCircle - select\n");
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    // LOG(INFO)("DeviceLayer::epdriver_DrawCircle - select ok\n");
    Paint_DrawCircle(_pc.x, _pc.y, _radius, static_cast<UWORD>(_imagecolor), static_cast<DOT_PIXEL>(_pointsize), static_cast<DRAW_FILL>(_drawfill));
    // LOG(INFO)("DeviceLayer::epdriver_DrawCircle - draw ok\n");
    return Result<void>::Success();
}

Result<void> DeviceLayer::epdriver_DrawChar(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, char _asciichar, Fontype _fontype, ImageColor _imagecolorF, ImageColor _imagecolorB)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawChar(_pc.x, _pc.y, _asciichar, _fontype, static_cast<UWORD>(_imagecolorF), static_cast<UWORD>(_imagecolorB));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawString_EN(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, std::string _string, Fontype _fontype, ImageColor _imagecolorF, ImageColor _imagecolorB)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawString_EN(_pc.x, _pc.y, _string.c_str(), _fontype, static_cast<UWORD>(_imagecolorF), static_cast<UWORD>(_imagecolorB));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawNum(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, Number _num, Fontype _fontype, ImageColor _imagecolorF, ImageColor _imagecolorB)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawNum(_pc.x, _pc.y, _num, _fontype, static_cast<UWORD>(_imagecolorF), static_cast<UWORD>(_imagecolorB));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawTime(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, Time _time, Fontype _fontype, ImageColor _imagecolorF, ImageColor _imagecolorB)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawTime(_pc.x, _pc.y, &_time, _fontype, static_cast<UWORD>(_imagecolorF), static_cast<UWORD>(_imagecolorB));
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_DrawDate(ImageBuffer_ptr _imagebuffer, PointCoordinates _pc, Time _time, Fontype _fontype, ImageColor _imagecolorF, ImageColor _imagecolorB)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    Paint_DrawDate(_pc.x, _pc.y, &_time, _fontype, static_cast<UWORD>(_imagecolorF), static_cast<UWORD>(_imagecolorB));
    return Result<void>::Success();
}
Result<Dimensions> DeviceLayer::epdriver_GetDrawRange(std::string _string, PointCoordinates _pc, Fontype _fontype)
{
    auto pString = _string.c_str();
    UWORD Xpoint = _pc.x;
    UWORD Ypoint = _pc.y;

    while (*pString != '\0')
    {
        // if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
        if ((Xpoint + _fontype->Width) > Paint.Width)
        {
            Xpoint = _pc.x;
            Ypoint += _fontype->Height;
        }

        // If the Y direction is full, reposition to(Xstart, Ystart)
        if ((Ypoint + _fontype->Height) > Paint.Height)
        {
            Xpoint = _pc.x;
            Ypoint = _pc.y;
        }

        // The next character of the address
        pString++;

        // The next word of the abscissa increases the font of the broadband
        Xpoint += _fontype->Width;
    }
    // Xpoint += _fontype->Width;
    Ypoint += _fontype->Height;
    return Result<Dimensions>::Success(Dimensions{static_cast<unsigned short>(Xpoint - _pc.x), static_cast<unsigned short>(Ypoint - _pc.y)});
}

Result<void> DeviceLayer::epdriver_ReadBmp(ImageBuffer_ptr _imagebuffer, std::string _path, PointCoordinates _pc)
{
    Paint_SelectImage(_imagebuffer->imgbuff_ptr);
    GUI_ReadBmp(_path.c_str(), _pc.x, _pc.y);
    return Result<void>::Success();
}
Result<void> DeviceLayer::epdriver_TouchInit(void)
{
    GT_Init();
    epdriver_Delay(200);
    return Result<void>::Success();
}
Result<PointCoordinates> DeviceLayer::epdriver_TouchScan(void) {
    UBYTE rt = GT_Scan_2();
    if (rt == 1) {
        return Result<PointCoordinates>::Error("No prepared Touch data");
    }

    // 获取当前时间
    auto currentTime = std::chrono::steady_clock::now();

    // 检查当前时间与上一次触摸时间的差值
    if (currentTime - lastTouchTime < std::chrono::milliseconds(500)) {
        // 如果差值小于500毫秒，则忽略这次触摸
        return Result<PointCoordinates>::Error("Touch event ignored due to debounce");
    }

    // 更新上一次触摸时间
    lastTouchTime = currentTime;

    // 返回触摸坐标
    return Result<PointCoordinates>::Success(PointCoordinates{Dev_Now.X[0], Dev_Now.Y[0]});
}