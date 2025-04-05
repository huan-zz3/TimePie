#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "predefine.h"
#include "epd_component.h"

class ProgressBar : public EPD_Component
{
public:
    ProgressBar(std::shared_ptr<DeviceLayer> driver);
    ~ProgressBar();
    Result<void> draw() override;

    Result<void> setendcordinate(PointCoordinates);
    Result<void> setProgress(uint8_t progress);
    Result<void> freshShow();

private:
    uint8_t progress_;
    PointCoordinates endcordinate_ = {0, 0};

protected:
    using EPD_Component::parentpage_;
    using EPD_Component::range_;
    using EPD_Component::startcordinate_;
    using EPD_Component::visible_;

    using EPD_Component::epd_driver_;
};

#endif /* PROGRESSBAR_H */