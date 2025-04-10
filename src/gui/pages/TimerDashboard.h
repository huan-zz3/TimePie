#ifndef TIMERDASHBOARD_H
#define TIMERDASHBOARD_H

#include "epd_pages.h"
#include "gui/components/button.h"
#include "gui/components/text.h"
#include "gui/components/progressbar.h"
// #include "bgservice/servicelayer.h"

class TimerDashboard : public EPD_Page
{
public:
    explicit TimerDashboard(std::shared_ptr<DeviceLayer> epdDriver);
    ~TimerDashboard();

    Result<void> draw() override;
    Result<void> show() override;
    Result<void> showclear();

    Result<void> startPageUpdate();
    Result<void> stopPageUpdate();
    Result<void> updatePage(uint32_t remainsec, uint32_t totalsec, const std::string &time);
    Result<void> updatePage(uint32_t passedsec, const std::string &time);

private:
    using EPD_Page::componentList_;
    using EPD_Page::componentToRange_;
    using EPD_Page::epd_driver_;
    using EPD_Page::imageBuffer_;

public:
    using EPD_Page::signal_Clicked_;
    Signal_void signal_Tomatofinished_;

private:
    Result<void> initcomponents();
    bool firstcompinit = true;

    std::shared_ptr<Text> nowtime;
    std::shared_ptr<Button> countdown;
    std::shared_ptr<ProgressBar> progressbar;

    // std::string starttime;
    // std::string stoptime;
};

#endif // TIMERDASHBOARD_H
