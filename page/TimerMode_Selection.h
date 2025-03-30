#ifndef TIMERMODE_SELECTION_H
#define TIMERMODE_SELECTION_H

#include "epd_pages.h"

#include "button.h"
#include "text.h"
#include <vector>
#include <map>

enum class TimerMode
{
    Five = 5,
    Ten = 10,
    Fifteen = 15,
    Twenty = 20,
    TwentyFive = 25,
    Thirty = 30,
    FortyFive = 45,
    Sixty = 60,
    Ninety = 90,
    OneEighty = 180,
    // Custom
};
constexpr std::array<TimerMode, 11> AllTimerModes = {
    TimerMode::Five,
    TimerMode::Ten,
    TimerMode::Fifteen,
    TimerMode::Twenty,
    TimerMode::TwentyFive,
    TimerMode::Thirty,
    TimerMode::FortyFive,
    TimerMode::Sixty,
    TimerMode::Ninety,
    TimerMode::OneEighty,
    // TimerMode::Custom
};
typedef sigc::slot<void, TimerMode> Slot_TimerMode;

class TimerMode_Selection : public EPD_Page
{
public:
    explicit TimerMode_Selection(std::shared_ptr<IEPD_Driver> epdDriver);
    ~TimerMode_Selection();

    Result<void> draw() override;
    Result<void> show() override;

private:
    using EPD_Page::componentList_;
    using EPD_Page::componentToRange_;
    using EPD_Page::epd_driver_;
    using EPD_Page::imageBuffer_;

public:
    using EPD_Page::signal_Clicked_;
    // using EPD_Page::signal_commonClicked_;
    sigc::signal<void, TimerMode> signal_clickedTimerMode_;

    Result<void> setPageNum(size_t pageNum);

private:
    Result<void> initcomponents();
    bool firstcompinit = true;

    // std::shared_ptr<Button> button_five, button_ten, button_fifteen, button_twenty, button_twentyFive, button_thirty, button_fortyFive, button_sixty, button_ninety, button_oneEighty, button_custom;
    std::map<TimerMode, std::shared_ptr<Button>> buttonMap;
    std::shared_ptr<Button> button_next, button_back;
};

#endif // TIMERMODE_SELECTION_H
