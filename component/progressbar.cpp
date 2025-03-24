#include "progressbar.h"

ProgressBar::ProgressBar(std::shared_ptr<IEPD_Driver> driver)
    : EPD_Component(driver)
{
}
ProgressBar::~ProgressBar()
{
}
Result<void> ProgressBar::draw()
{
    // 绘制进度条组件
    const auto imageptr = parentpage_->getimagebuffer().successvalue();
    const auto totalW = endcordinate_.x - startcordinate_.x;
    const auto totalH = endcordinate_.y - startcordinate_.y;
    const auto progressW = totalW * progress_ / 100;
    // const auto progressH = totalH * progress_ / 100;
    PointCoordinates progressCordnate = {startcordinate_.x + progressW, startcordinate_.y + totalH};

    epd_driver_->epdriver_DrawRectangle(imageptr, startcordinate_, endcordinate_, ImageColor::Black, PointSize::X22, DrawFill::NoFill);
    epd_driver_->epdriver_DrawRectangle(imageptr, startcordinate_, progressCordnate, ImageColor::Black, PointSize::X11, DrawFill::Fill);

    // 更新组件范围range
    if (range_.empty())
    {
        range_.push_back({{startcordinate_}, {endcordinate_}});
    }
    else
    {
        range_.pop_front();
        range_.push_back({{startcordinate_}, {endcordinate_}});
    }
    // 将组件范围range同步至父页面
    auto convertpointer = std::static_pointer_cast<EPD_Component>(shared_from_this());
    if (convertpointer == nullptr)
    {
        return Result<void>::Error("ProgressBar::draw::convertpointer err");
    }
    parentpage_->updatecomponentrange(convertpointer, range_);

    return Result<void>::Success();
}
void ProgressBar::slot_Clicked_()
{
    /* void */
}
Result<void> ProgressBar::setendcordinate(PointCoordinates _pc)
{
    endcordinate_ = _pc;
    return Result<void>::Success();
}
Result<void> ProgressBar::setProgress(uint8_t _progress)
{
    progress_ = _progress;
}
Result<void> ProgressBar::freshShow()
{
    const auto imageptr = parentpage_->getimagebuffer().successvalue();
    draw();
    epd_driver_->epdriver_Init(InitMode::Part);
    epd_driver_->epdriver_Display(imageptr, DisplayMode::Partial_Wait);
    epd_driver_->epdriver_Sleep();
    return Result<void>::Success();
}