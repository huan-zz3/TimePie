#ifndef BUTTON_H
#define BUTTON_H

#include "predefine.h"
#include "epd_component.h"
#include "iepd_driver.h"

class Button : public EPD_Component
{
public:
    Button(std::shared_ptr<IEPD_Driver> driver);
    ~Button();
    Result<void> draw() override;

    Result<void> set_text(std::string text);
    Result<void> enable_border(bool);
    Result<void> set_border(uint8_t border_width, uint8_t padding);
    Result<void> set_font(sFONT *_font);
    Result<void> set_color(ImageColor fontcolr, ImageColor backcolr);
    
    Result<void> setall(std::string text, PointCoordinates pc, bool has_border, uint8_t border_width, uint8_t padding, sFONT *_font);

private:
    std::string text_ = "";
    bool has_border_ = true;
    PointSize border_width_ = PointSize::X22;   // 1~8 pixel
    uint8_t padding_ = 2;

    sFONT *font_ = Font16;
    ImageColor fontcolr_ = ImageColor::Black;
    ImageColor backcolr_ = ImageColor::White;

protected:
    using EPD_Component::parentpage_;
    using EPD_Component::range_;
    using EPD_Component::visible_ ;

    using EPD_Component::epd_driver_;
};

#endif /* BUTTON_H */