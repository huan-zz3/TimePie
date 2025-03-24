#include "TimerMode_Selection.h"

TimerMode_Selection::TimerMode_Selection(std::shared_ptr<IEPD_Driver> _epdd)
    : EPD_Page(std::move(_epdd))
{
}
TimerMode_Selection::~TimerMode_Selection()
{
}
Result<void> TimerMode_Selection::draw()
{
    // 从z较小的开始
    for (auto it = componentList_.begin(); it != componentList_.end(); ++it)
    {
        auto component = *it;
        if (!component)
            continue; // 确保组件指针有效

        auto rt = component->draw();  // 无需传入页面buffer，组件会自动获取
        if(!rt.isSuccess()){
            return Result<void>::Error("TimerMode_Selection::draw() component->draw() failed");
        }
    }
    return Result<void>::Success();
}
Result<void> TimerMode_Selection::show()
{
    epd_driver_->epdriver_Init(InitMode::Full);
    // epd_driver_->epdriver_Display(imageBuffer_, DisplayMode::Normal);
    epd_driver_->epdriver_Clear(ClearMode::White);
    epd_driver_->epdriver_Init(InitMode::Full);
    epd_driver_->epdriver_Display(imageBuffer_, DisplayMode::Normal);
    epd_driver_->epdriver_Delay(1000);
    epd_driver_->epdriver_Sleep();
    return Result<void>::Success();
}
