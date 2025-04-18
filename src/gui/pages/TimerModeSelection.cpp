#include "TimerModeSelection.h"
TimerModeSelection::TimerModeSelection(std::shared_ptr<DeviceLayer> _epdd) :
    EPD_Page(_epdd) {
}
TimerModeSelection::~TimerModeSelection() {
    for (const auto &mode : AllTimerModes) {
        buttonMap[mode].reset();
    }
    button_next.reset();
    button_back.reset();
}
Result<void> TimerModeSelection::draw() {
    // 清白buffer
    epd_driver_->epdriver_imgClear(imageBuffer_, ImageColor::White);
    // 从z较小的开始
    for (auto it = componentList_.begin(); it != componentList_.end(); ++it) {
        auto component = *it;
        if (!component)
            continue; // 确保组件指针有效
        if (!component->getvisable().successvalue())
            continue; // 确保组件可见

        auto rt = component->draw(); // 无需传入页面buffer，组件会自动获取
        if (!rt.isSuccess()) {
            return Result<void>::Error("TimerModeSelection::draw() component->draw() failed");
        }
    }
    return Result<void>::Success();
}
Result<void> TimerModeSelection::show() {
    epd_driver_->epdriver_Init(InitMode::Full);
    epd_driver_->epdriver_Display(imageBuffer_, DisplayMode::Normal);
    // epd_driver_->epdriver_Delay(500);
    epd_driver_->epdriver_Sleep();
    return Result<void>::Success();
}
Result<void> TimerModeSelection::initcomponents() {
    for (const auto &mode : AllTimerModes) {
        buttonMap[mode] = std::make_shared<Button>(epd_driver_);
        addcomponent(buttonMap[mode]);
    }
    button_next = std::make_shared<Button>(epd_driver_);
    addcomponent(button_next);
    button_back = std::make_shared<Button>(epd_driver_);
    addcomponent(button_back);

    auto _font = Font24;
    auto _width = 2;
    auto _margin = 4;

    {
        buttonMap[TimerMode::Five]->setall("5m", {10, 20}, true, _width, _margin, _font);
        buttonMap[TimerMode::Ten]->setall("10m", {90, 20}, true, _width, _margin, _font);
        buttonMap[TimerMode::Fifteen]->setall("15m", {180, 20}, true, _width, _margin, _font);
        buttonMap[TimerMode::Twenty]->setall("20m", {10, 80}, true, _width, _margin, _font);
        buttonMap[TimerMode::TwentyFive]->setall("25m", {90, 80}, true, _width, _margin, _font);
        button_next->setall("N.", {180, 80}, true, _width, _margin, _font);
    }
    {
        buttonMap[TimerMode::Thirty]->setall("30m", {10, 20}, true, _width, _margin, _font);
        buttonMap[TimerMode::FortyFive]->setall("45m", {90, 20}, true, _width, _margin, _font);
        buttonMap[TimerMode::Sixty]->setall("60m", {180, 20}, true, _width, _margin, _font);
        buttonMap[TimerMode::Ninety]->setall("90m", {10, 80}, true, _width, _margin, _font);
        buttonMap[TimerMode::CountUP]->setall("++m", {90, 80}, true, _width, _margin, _font);
        button_back->setall("B.", {180, 80}, true, _width, _margin, _font);
    }
    // 设置点击事件
    {
        buttonMap[TimerMode::Five]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Five); });
        buttonMap[TimerMode::Ten]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Ten); });
        buttonMap[TimerMode::Fifteen]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Fifteen); });
        buttonMap[TimerMode::Twenty]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Twenty); });
        buttonMap[TimerMode::TwentyFive]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::TwentyFive); });
        button_next->signal_clicked_.connect([this]() { setPageNum(2); draw(); show(); });
    }
    {
        buttonMap[TimerMode::Thirty]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Thirty); });
        buttonMap[TimerMode::FortyFive]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::FortyFive); });
        buttonMap[TimerMode::Sixty]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Sixty); });
        buttonMap[TimerMode::Ninety]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::Ninety); });
        buttonMap[TimerMode::CountUP]->signal_clicked_.connect([this]() { signal_clickedTimerMode_.emit(TimerMode::CountUP); });
        button_back->signal_clicked_.connect([this]() { setPageNum(1); draw(); show(); });
    }
    { // 设置前页后页信号连接
        signal_clickeyNext_.connect([this]() { button_next->signal_clicked_.emit(); });
        signal_clickeyPrev_.connect([this]() { button_back->signal_clicked_.emit(); });
    }

    return Result<void>::Success();
}
Result<void> TimerModeSelection::setPageNum(uint8_t pageNum) {
    // 如果是第一次绘制，则进行组件初始化
    if (firstcompinit) {
        initcomponents();
        firstcompinit = false;
    }

    switch (pageNum) {
    case 1:
        buttonMap[TimerMode::Five]->setvisable(true);
        buttonMap[TimerMode::Ten]->setvisable(true);
        buttonMap[TimerMode::Fifteen]->setvisable(true);
        buttonMap[TimerMode::Twenty]->setvisable(true);
        buttonMap[TimerMode::TwentyFive]->setvisable(true);
        button_next->setvisable(true);

        buttonMap[TimerMode::Thirty]->setvisable(false);
        buttonMap[TimerMode::FortyFive]->setvisable(false);
        buttonMap[TimerMode::Sixty]->setvisable(false);
        buttonMap[TimerMode::Ninety]->setvisable(false);
        buttonMap[TimerMode::CountUP]->setvisable(false);
        button_back->setvisable(false);
        break;

    case 2:
        buttonMap[TimerMode::Five]->setvisable(false);
        buttonMap[TimerMode::Ten]->setvisable(false);
        buttonMap[TimerMode::Fifteen]->setvisable(false);
        buttonMap[TimerMode::Twenty]->setvisable(false);
        buttonMap[TimerMode::TwentyFive]->setvisable(false);
        button_next->setvisable(false);

        buttonMap[TimerMode::Thirty]->setvisable(true);
        buttonMap[TimerMode::FortyFive]->setvisable(true);
        buttonMap[TimerMode::Sixty]->setvisable(true);
        buttonMap[TimerMode::Ninety]->setvisable(true);
        buttonMap[TimerMode::CountUP]->setvisable(true);
        button_back->setvisable(true);
        break;
    default:
        return Result<void>::Error("TimerModeSelection::setPageNum() pageNum error");
    }
    return Result<void>::Success();
}