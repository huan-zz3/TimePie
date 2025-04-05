#ifndef TIMERDASHBOARD_H
#define TIMERDASHBOARD_H

#include "epd_pages.h"
#include "gui/components/button.h"
#include "gui/components/text.h"
#include "gui/components/progressbar.h"

class TimerDashboard : public EPD_Page
{
public:
    explicit TimerDashboard(std::shared_ptr<DeviceLayer> epdDriver);
    ~TimerDashboard();

    Result<void> draw() override;
    Result<void> show() override;

    Result<void> startPageUpdate(size_t);
    Result<void> stopPageUpdate();

private:
    using EPD_Page::componentList_;
    using EPD_Page::componentToRange_;
    using EPD_Page::epd_driver_;
    using EPD_Page::imageBuffer_;

public:
    using EPD_Page::signal_Clicked_;
    Signal_void signal_finished_;

private:
    Result<void> initcomponents();
    bool firstcompinit = true;

    std::shared_ptr<Text> nowtime;
    std::shared_ptr<Button> countdown;
    std::shared_ptr<ProgressBar> progressbar;
    std::shared_ptr<ServiceLayer> servicelayer;
};

#endif // TIMERDASHBOARD_H
