#include "TimerDashboard.h"
TimerDashboard::TimerDashboard(std::shared_ptr<DeviceLayer> _epdd)
    : EPD_Page(std::move(_epdd))
{
    signal_finished_.connect([this]()
                             { stopPageUpdate(); });
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
    // 如果是第一次绘制，则进行组件初始化
    if (firstcompinit)
    {
        initcomponents();
        firstcompinit = false;
    }
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

    auto rt = ServiceLayer::nowTimestr();
    if (!rt.isSuccess())
    {
        std::cout << rt.errormsg() << std::endl;
        return Result<void>::Error("TimerDashboard::initcomponents() ServiceLayer::nowTimestr() failed");
    }
    std::cout << "TimerDashboard::initcomponents() " << rt.successvalue() << std::endl;

    // 设置各组件属性
    nowtime->set_text(rt.successvalue());
    nowtime->setstartcordinate({10, 10});
    nowtime->set_font(Font12);

    countdown->set_text("000");
    countdown->set_border(1, 10);
    countdown->setstartcordinate({80, 40});
    countdown->set_font(Font24);

    progressbar->setstartcordinate({20, 100});
    progressbar->setendcordinate({230, 120});
    progressbar->setProgress(0);

    countdown->signal_clicked_.connect([this]()
                                       {
        std::cout << "TimerDashboard::countdown clicked" << std::endl;
        signal_finished_.emit(); });

    // 配置组件都显示
    nowtime->setvisable(true);
    countdown->setvisable(true);
    progressbar->setvisable(true);

    return Result<void>::Success();
}
Result<void> TimerDashboard::startPageUpdate(size_t countdown_minutes)
{
    if (countdown_minutes == 0)
    { // 正计时部分
        servicelayer->on_tomatotimer_updated.connect([this]()
                                                     {
            static size_t tomatocount = 0;
            tomatocount += 1;

            countdown->set_text(std::to_string(tomatocount));
            nowtime->set_text(ServiceLayer::nowTimestr().successvalue()); 
            progressbar->setProgress(0);

            draw();
            show(); 
        });
        servicelayer->epdserStartTomatoTimer(60);
    }
    else
    { // 倒计时部分
        servicelayer->on_tomatotimer_updated.connect([this, countdown_minutes]()
                                                     {
            static size_t tomatocount = 0;
            tomatocount += 1;

            countdown->set_text(std::to_string(countdown_minutes - tomatocount));
            nowtime->set_text(ServiceLayer::nowTimestr().successvalue()); 
            progressbar->setProgress((countdown_minutes - tomatocount) * 100 / countdown_minutes);

            draw();
            show();

            if(tomatocount >= countdown_minutes){
                stopPageUpdate();
                signal_finished_.emit();
                return;
            } 
        });

        servicelayer->epdserStartTomatoTimer(60);
    }

    return Result<void>::Success();
}
Result<void> TimerDashboard::stopPageUpdate()
{
    servicelayer->epdserStopTomatoTimer();
    servicelayer->on_tomatotimer_updated.clear();
    return Result<void>::Success();
}