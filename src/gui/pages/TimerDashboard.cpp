#include "TimerDashboard.h"
TimerDashboard::TimerDashboard(std::shared_ptr<DeviceLayer> _epdd)
    : EPD_Page(std::move(_epdd))
{
    // signal_finished_.connect([this]()
    //                          { stopPageUpdate(); });
}
TimerDashboard::~TimerDashboard()
{
    nowtime.reset();
    countdown.reset();
    progressbar.reset();
}
Result<void> TimerDashboard::draw()
{
    std::cout << "TimerDashboard::draw()" << std::endl;
    // 清白buffer
    epd_driver_->epdriver_imgClear(imageBuffer_, ImageColor::White);
    // 从z较小的开始
    for (auto it = componentList_.begin(); it != componentList_.end(); ++it)
    {
        auto component = *it;
        if (!component)
            continue; // 确保组件指针有效

        auto rt = component->draw(); // 无需传入页面buffer，组件会自动获取
        if (!rt.isSuccess())
        {
            return Result<void>::Error("TimerMode_Selection::draw() component->draw() failed");
        }
    }
    return Result<void>::Success();
}
Result<void> TimerDashboard::show()
{
    epd_driver_->epdriver_Init(InitMode::Full);
    epd_driver_->epdriver_Display(imageBuffer_, DisplayMode::Normal);
    epd_driver_->epdriver_Delay(500);
    epd_driver_->epdriver_Sleep();
    return Result<void>::Success();
}
Result<void> TimerDashboard::initcomponents()
{
    nowtime = std::make_shared<Text>(epd_driver_);
    countdown = std::make_shared<Button>(epd_driver_);
    progressbar = std::make_shared<ProgressBar>(epd_driver_);
    addcomponent(nowtime);
    addcomponent(countdown);
    addcomponent(progressbar);

    // 设置各组件属性
    nowtime->set_text("xx:xx");
    nowtime->setstartcordinate({10, 10});
    nowtime->set_font(Font12);

    countdown->set_text("000");
    countdown->set_border(1, 10);
    countdown->setstartcordinate({80, 40});
    countdown->set_font(Font24);

    progressbar->setstartcordinate({20, 100});
    progressbar->setendcordinate({230, 120});
    progressbar->setProgress(0);

    // countdown->signal_clicked_.connect([this]()
    //                                    {
    //     std::cout << "TimerDashboard::countdown clicked" << std::endl;
    //     signal_finished_.emit(); });

    // 配置组件都显示
    nowtime->setvisable(true);
    countdown->setvisable(true);
    progressbar->setvisable(true);

    return Result<void>::Success();
}
Result<void> TimerDashboard::startPageUpdate()
{
    // 如果是第一次绘制，则进行组件初始化
    if (firstcompinit)
    {
        initcomponents();
        firstcompinit = false;
    }
    return Result<void>::Success();
}
Result<void> TimerDashboard::stopPageUpdate()
{
    /* Nothing should do */
    return Result<void>::Success();
}
Result<void> TimerDashboard::updatePage(uint32_t remainsec, uint32_t totalsec, const std::string &time)
{

    countdown->set_text(std::to_string(remainsec));
    nowtime->set_text(time);
    std::cout << "remainsec: " << remainsec << " totalsec: " << totalsec << std::endl;
    uint8_t progress = static_cast<uint8_t>((remainsec * 100) / totalsec);
    std::cout << "Progress: " << static_cast<int>(progress) << std::endl;
    progressbar->setProgress(progress);

    draw();
    show();

    return Result<void>::Success();
}
Result<void> TimerDashboard::updatePage(uint32_t passedsec, const std::string &time)
{
    countdown->set_text(std::to_string(passedsec));
    nowtime->set_text(time);
    progressbar->setProgress(0);

    draw();
    show();

    return Result<void>::Success();
}