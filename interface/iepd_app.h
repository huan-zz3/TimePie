#ifndef IEPD_APP_H
#define IEPD_APP_H

#include "predefine.h"
#include "iepd_service.h"
#include "iepd_driver.h"
#include "epd_pages.h"
#include <memory>

class IEPD_app
{
public:
    explicit IEPD_app() {};

    virtual Result<void> epdappInit() = 0;
    virtual Result<void> epdappStart() = 0;
    virtual Result<void> epdappStop() = 0;
    virtual Result<void> reFreshPage() = 0;

public: // slots
public: // signals
protected:
    std::shared_ptr<IEPDService> epd_service_;
    std::shared_ptr<IEPD_Driver> epd_driver_;
};

#endif