#ifndef I_EPD_APP_H
#define I_EPD_APP_H

#include "predefine.h"


class I_EPD_app
{
public:
    explicit I_EPD_app();

    virtual void epdinit(Result<void>) = 0;
    virtual void epdSleep(Result<void>) = 0;
    virtual void showMenu(Result<void>) = 0;
    virtual void reFreshPage(Result<void>) = 0;

private:

};

#endif