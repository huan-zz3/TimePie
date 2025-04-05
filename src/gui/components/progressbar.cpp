#include "progressbar.h"

ProgressBar::ProgressBar(std::shared_ptr<DeviceLayer> driver)
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

    // 计算右上和左下点的坐标
    auto _rupointer = PointCoordinates{static_cast<unsigned short>(endcordinate_.x), startcordinate_.y};
    auto _llpointer = PointCoordinates{startcordinate_.x, static_cast<unsigned short>(endcordinate_.y)};

    // 更新组件范围range
    if (range_.empty())
        range_.clear();

    range_.push_back({{startcordinate_}, {_rupointer}, {endcordinate_}, {_llpointer}});

    // 将组件范围range同步至父页面
    auto convertpointer = std::static_pointer_cast<EPD_Component>(shared_from_this());
    if (convertpointer == nullptr)
    {
        return Result<void>::Error("ProgressBar::draw::convertpointer err");
    }
    parentpage_->updatecomponentrange(convertpointer, range_);

    return Result<void>::Success();
}
Result<void> ProgressBar::setendcordinate(PointCoordinates _pc)
{
    endcordinate_ = _pc;
    return Result<void>::Success();
}
Result<void> ProgressBar::setProgress(uint8_t _progress)
{
    progress_ = _progress;
    return Result<void>::Success();
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