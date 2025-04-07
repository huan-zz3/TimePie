#ifndef TIMERCATEGORYGRID_H
#define TIMERCATEGORYGRID_H

#include "epd_pages.h"
#include "gui/components/button.h"
#include "gui/components/text.h"
#include "gui/components/progressbar.h"

enum class TimerCategory
{
    Study,
    Read,
    Transport,
    Relax,
    Social,
    DailyAffair,
    HaveFun,
    Sport,
    SelfEnhance,
    Sleep,
    News,
    Sundry
};
constexpr std::array<TimerCategory, 12> AllTimerCategory = {
    TimerCategory::Study,
    TimerCategory::Read,
    TimerCategory::Transport,
    TimerCategory::Relax,
    TimerCategory::Social,
    TimerCategory::DailyAffair,
    TimerCategory::HaveFun,
    TimerCategory::Sport,
    TimerCategory::SelfEnhance,
    TimerCategory::Sleep,
    TimerCategory::News,
    TimerCategory::Sundry
};

class TimerCategoryGrid : public EPD_Page
{
public:
    explicit TimerCategoryGrid(std::shared_ptr<DeviceLayer> epdDriver);
    ~TimerCategoryGrid();

    Result<void> draw() override;
    Result<void> show() override;

private:
    using EPD_Page::componentList_;
    using EPD_Page::componentToRange_;
    using EPD_Page::epd_driver_;
    using EPD_Page::imageBuffer_;

public:
    using EPD_Page::signal_Clicked_;

    sigc::signal<void, TimerCategory> signal_clickedTimerCategory_;
    Result<void> setPageNum(uint8_t pageNum);

private:
    Result<void> initcomponents();
    bool firstcompinit = true;

    std::map<TimerCategory, std::shared_ptr<Button>> buttonMap;
    std::shared_ptr<Button> button_next, button_back;
};

#endif // TIMERCATEGORYGRID_H
