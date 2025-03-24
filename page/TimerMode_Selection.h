#ifndef TIMERMODE_SELECTION_H
#define TIMERMODE_SELECTION_H

#include "epd_pages.h"

class TimerMode_Selection : public EPD_Page
{
public:
    TimerMode_Selection(std::shared_ptr<IEPD_Driver> _epdd);
    ~TimerMode_Selection();
    Result<void> draw() override;
    Result<void> show() override;

protected:
    using EPD_Page::epd_driver_;
    using EPD_Page::imageBuffer_;
    using EPD_Page::componentList_;
    using EPD_Page::componentToRange_;
private:


public:
    using EPD_Page::signal_Clicked_;

};

#endif // TIMERMODE_SELECTION_H