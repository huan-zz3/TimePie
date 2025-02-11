#include "uilayer.h"

UILayer::UILayer(std::unique_ptr<IEPDService> _epds)
{
    epd_service_ = std::move(_epds);
}
void UILayer::epdappInit(Result<void>)
{
}
void UILayer::epdappSleep(Result<void>)
{
}
void UILayer::reFreshPage(Result<void>)
{
}

void UILayer::on_showMenu(Result<void>)
{
}

void UILayer::click_start25minsTomato(Result<void>)
{
}
void UILayer::click_start5minsRest(Result<void>)
{
}
void UILayer::click_startForwardRecord(Result<void>)
{
}
void UILayer::click_stopTomato(Result<void>)
{
}