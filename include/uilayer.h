#ifndef UILAYER_H
#define UILAYER_H

#include "predefine.h"
#include "iepd_app.h"

class UILayer : public IEPD_app
{
public:
    UILayer(std::unique_ptr<IEPDService>);
    void epdappInit(Result<void>);
    void epdappSleep(Result<void>);
    void reFreshPage(Result<void>);

    void on_showMenu(Result<void>);

    void click_start25minsTomato(Result<void>);
    void click_start5minsRest(Result<void>);
    void click_startForwardRecord(Result<void>);
    void click_stopTomato(Result<void>);

public:
    using IEPD_app::refreshpage_signal_;

    using IEPD_app::click_start25minstomato_signal_;
    using IEPD_app::click_start5minsrest_signal_;
    using IEPD_app::click_startforwardrecord_signal_;
    using IEPD_app::click_stoptomato_signal_;
    using IEPD_app::on_showmenu_signal_;

private:
    using IEPD_app::epd_service_;
};

#endif