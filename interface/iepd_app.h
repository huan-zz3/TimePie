#ifndef IEPD_APP_H
#define IEPD_APP_H

#include "predefine.h"
#include "iepd_service.h"
#include "memory"

class IEPD_app
{
public:
    // explicit IEPD_app(std::unique_ptr<IEPDService>);
    explicit IEPD_app(){};

    virtual Result<void> epdappInit() = 0;
    virtual Result<void> epdappSleep() = 0;
    virtual Result<void> reFreshPage() = 0;

    virtual void on_showMenu(Result<void>) = 0;

    virtual void click_start25minsTomato(Result<void>) = 0;
    virtual void click_start5minsRest(Result<void>) = 0;
    virtual void click_startForwardRecord(Result<void>) = 0;
    // virtual void click_pasueTomato(Result<void>) = 0;// There should not be a pause in Tomato Clock
    // virtual void click_resumeTomato(Result<void>) = 0; 
    virtual void click_stopTomato(Result<void>) = 0;

    // virtual void showTomatoPage(Result<void>) = 0;
    // virtual void startTomato(Result<void>) = 0;
    // virtual void pauseTomato(Result<void>) = 0;
    // virtual void resumeTomato(Result<void>) = 0;
    // virtual void stopTomato(Result<void>) = 0;
    // virtual void saveTomato(Result<void>) = 0;

public:
    Signal_void refreshpage_signal_;

    Signal_void on_showmenu_signal_;
    Signal_void click_start25minstomato_signal_;
    Signal_void click_start5minsrest_signal_;
    Signal_void click_startforwardrecord_signal_;
    Signal_void click_stoptomato_signal_;



protected:
    std::unique_ptr<IEPDService> epd_service_;

};

#endif