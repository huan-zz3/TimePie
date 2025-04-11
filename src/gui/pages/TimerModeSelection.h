#ifndef TIMERMODESELECTION_H
#define TIMERMODESELECTION_H

#include "epd_pages.h"

#include "gui/components/button.h"
#include "gui/components/text.h"
#include <vector>
#include <map>

enum class TimerMode {
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
    CountUP = 0
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
    TimerMode::CountUP};
typedef sigc::slot<void, TimerMode> Slot_TimerMode;

class TimerModeSelection : public EPD_Page {
public:
    explicit TimerModeSelection(std::shared_ptr<DeviceLayer> epdDriver);
    ~TimerModeSelection();

    Result<void> draw() override;
    Result<void> show() override;

private:
    using EPD_Page::componentList_;
    using EPD_Page::epd_driver_;
    using EPD_Page::imageBuffer_;
    using EPD_Page::componentToRange_;

public:
    using EPD_Page::signal_Clicked_;

    sigc::signal<void, TimerMode> signal_clickedTimerMode_;
    Result<void> setPageNum(uint8_t pageNum);

private:
    Result<void> initcomponents();
    bool firstcompinit = true;

    std::map<TimerMode, std::shared_ptr<Button>> buttonMap;
    std::shared_ptr<Button> button_next, button_back;
};

#endif // TIMERMODESELECTION_H
