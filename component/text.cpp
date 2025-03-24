#include "text.h"

Text::Text(std::shared_ptr<IEPD_Driver> driver)
    : EPD_Component(driver)
{
}
Text::~Text()
{
}
Result<void> Text::draw()
{
    // 绘制文本
    const auto imageptr = parentpage_->getimagebuffer().successvalue();
    epd_driver_->epdriver_DrawString_EN(imageptr, startcordinate_, text_, font_, fontcolr_, backcolr_);
    auto _rt1 = epd_driver_->epdriver_GetDrawRange(text_, startcordinate_, font_);
    if (!_rt1.isSuccess())
    {
        return Result<void>::Error("Text::draw::epdriver_GetDrawRange err");
    }
    // 更新组件范围range
    const auto _endpoint_x = startcordinate_.x + _rt1.successvalue().w;
    const auto _endpoint_y = startcordinate_.y + _rt1.successvalue().h;
    const auto _endpoint = PointCoordinates{_endpoint_x, _endpoint_y};
    if (range_.empty())
    {
        range_.push_back({{startcordinate_}, {_endpoint}});
    }
    else
    {
        range_.pop_front();
        range_.push_back({{startcordinate_}, {_endpoint}});
    }
    // 将组件范围range同步至父页面
    auto convertpointer = std::static_pointer_cast<EPD_Component>(shared_from_this());
    if (convertpointer == nullptr)
    {
        return Result<void>::Error("Text::draw::convertpointer err");
    }
    parentpage_->updatecomponentrange(convertpointer, range_);

    return Result<void>::Success();
}
void Text::slot_Clicked_()
{
    /* void */
}
Result<void> Text::set_text(std::string text)
{
    text_ = text;
    return Result<void>::Success();
}
Result<void> Text::set_font(sFONT *_font)
{
    font_ = _font;
    return Result<void>::Success();
}
Result<void> Text::set_color(ImageColor fontcolr, ImageColor backcolr)
{
    fontcolr_ = fontcolr;
    backcolr_ = backcolr;
    return Result<void>::Success();
}