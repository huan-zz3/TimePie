#include "button.h"

Button::Button(std::shared_ptr<IEPD_Driver> driver)
    : EPD_Component(driver)
{
}
Button::~Button()
{
}
Result<void> Button::draw()
{
    auto _textstartcord = startcordinate_;
    const auto imageptr = parentpage_->getimagebuffer().successvalue();
    PointCoordinates _endpoint = {0, 0}, _rupointer = {0, 0}, _llpointer = {0, 0};
    // 获取文本的绘制范围
    auto _rt1 = epd_driver_->epdriver_GetDrawRange(text_, startcordinate_, font_);
    if (!_rt1.isSuccess())
    {
        return Result<void>::Error("Text::draw::epdriver_GetDrawRange err");
    }

    if (has_border_)
    {
        // 计算外框的终点坐标
        const auto _endpoint_x = startcordinate_.x + _rt1.successvalue().w + padding_ * static_cast<unsigned short>(2);
        const auto _endpoint_y = startcordinate_.y + _rt1.successvalue().h + padding_ * static_cast<unsigned short>(2);
        Debug("Button::draw::has_border_ _endpoint_x:%d _endpoint_y:%d \n", _endpoint_x, _endpoint_y);
        _endpoint = PointCoordinates{static_cast<unsigned short>(_endpoint_x), static_cast<unsigned short>(_endpoint_y)};

        // 计算右上和左下点的坐标
        _rupointer = PointCoordinates{static_cast<unsigned short>(_endpoint_x), startcordinate_.y};
        _llpointer = PointCoordinates{startcordinate_.x, static_cast<unsigned short>(_endpoint_y)};

        // 更新文本起始坐标
        _textstartcord.x += padding_;
        _textstartcord.y += padding_;

        // 绘制文本,需在绘制外框之前
        epd_driver_->epdriver_DrawString_EN(imageptr, _textstartcord, text_, font_, fontcolr_, backcolr_);
        // 绘制外框
        epd_driver_->epdriver_DrawRectangle(imageptr, startcordinate_, _endpoint, fontcolr_, border_width_, DrawFill::NoFill);
    }
    else
    {
        // 计算文本的终点坐标
        const auto _endpoint_x = startcordinate_.x + _rt1.successvalue().w;
        const auto _endpoint_y = startcordinate_.y + _rt1.successvalue().h;
        _endpoint = PointCoordinates{static_cast<unsigned short>(_endpoint_x), static_cast<unsigned short>(_endpoint_y)};

        // 计算右上和左下点的坐标
        _rupointer = PointCoordinates{static_cast<unsigned short>(_endpoint_x), startcordinate_.y};
        _llpointer = PointCoordinates{startcordinate_.x, static_cast<unsigned short>(_endpoint_y)};

        // 绘制文本
        epd_driver_->epdriver_DrawString_EN(imageptr, _textstartcord, text_, font_, fontcolr_, backcolr_);
    }

    // 若range_不为空，则清空
    if (!range_.empty())
        range_.clear();

    // 更新组件范围range
    range_.push_back({{startcordinate_}, {_rupointer}, {_llpointer}, {_endpoint}});

    printComponentRange(range_);
    // 将组件范围range同步至父页面
    auto convertpointer = std::static_pointer_cast<EPD_Component>(shared_from_this());
    if (convertpointer == nullptr)
    {
        return Result<void>::Error("Button::draw::convertpointer err");
    }
    parentpage_->updatecomponentrange(convertpointer, range_);

    return Result<void>::Success();
}
// void Button::slot_Clicked_()
// {
//     Debug("Button::slot_Clicked_");
// }
Result<void> Button::set_text(std::string text)
{
    text_ = text;
    return Result<void>::Success();
}
Result<void> Button::enable_border(bool _enable)
{
    has_border_ = _enable;
    return Result<void>::Success();
}
Result<void> Button::set_border(uint8_t _border_width, uint8_t _padding)
{
    switch (_border_width)
    {
    case 0:
        return Result<void>::Error("Button::set_border::border_width_ err");
    case 1:
        border_width_ = PointSize::X11;
        break;
    case 2:
        border_width_ = PointSize::X22;
        break;
    case 3:
        border_width_ = PointSize::X33;
        break;
    case 4:
        border_width_ = PointSize::X44;
        break;
    case 5:
        border_width_ = PointSize::X55;
        break;
    case 6:
        border_width_ = PointSize::X66;
        break;
    case 7:
        border_width_ = PointSize::X77;
        break;
    case 8:
        border_width_ = PointSize::X88;
        break;
    default:
        border_width_ = PointSize::X88;
        break;
    }

    padding_ = _padding;
    return Result<void>::Success();
}
Result<void> Button::set_font(sFONT *_font)
{
    font_ = _font;
    return Result<void>::Success();
}
Result<void> Button::set_color(ImageColor fontcolr, ImageColor backcolr)
{
    fontcolr_ = fontcolr;
    backcolr_ = backcolr;
    return Result<void>::Success();
}
Result<void> Button::setall(std::string text, PointCoordinates pc, bool has_border, uint8_t border_width, uint8_t padding, sFONT *_font)
{
    set_text(text);
    setstartcordinate(pc);
    enable_border(has_border);
    set_border(border_width, padding);
    set_font(_font);
    return Result<void>::Success();
}