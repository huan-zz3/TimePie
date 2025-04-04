#ifndef TEXT_H
#define TEXT_H

#include "predefine.h"
#include "epd_component.h"
#include "iepd_driver.h"

class Text : public EPD_Component
{
public:
    Text(std::shared_ptr<IEPD_Driver> driver);
    ~Text();
    Result<void> draw() override;

    Result<void> set_text(std::string text);
    Result<void> set_font(sFONT *_font);
    Result<void> set_color(ImageColor fontcolr, ImageColor backcolr);

private:
    std::string text_ ={};
    sFONT *font_ = Font16;
    ImageColor fontcolr_ = ImageColor::Black;
    ImageColor backcolr_ = ImageColor::White;

protected:
    using EPD_Component::parentpage_;
    using EPD_Component::range_;
    using EPD_Component::startcordinate_;
    using EPD_Component::visible_;

    using EPD_Component::epd_driver_;
};

#endif /* TEXT_H */