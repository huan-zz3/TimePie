#include "epd_component.h"

EPD_Component::EPD_Component(std::shared_ptr<DeviceLayer> _driver)
    : epd_driver_(_driver)
{
}
EPD_Component::~EPD_Component()
{
    delete_remove();
}
Result<void> EPD_Component::setstartcordinate(PointCoordinates _pc)
{
    startcordinate_ = _pc;
    return Result<void>::Success();
}
Result<void> EPD_Component::setparentpage(std::shared_ptr<EPD_Page> _page)
{
    parentpage_ = _page;
    return Result<void>::Success();
}
Result<void> EPD_Component::setvisable(bool _visable)
{
    auto tishpointer = shared_from_this();
    if (tishpointer == nullptr)
    {
        return Result<void>::Error("EPD_Component::setvisable::tishpointer err");
    }

    if (_visable)
    {
        parentpage_->addcomponent(tishpointer);
    }
    else
    {
        parentpage_->removecomponent(tishpointer);
    }
    visible_ = _visable;

    return Result<void>::Success();
}
Result<bool> EPD_Component::getvisable()
{
    return Result<bool>::Success(visible_);
}
Result<void> EPD_Component::delete_remove()
{
    setparentpage(nullptr);
    parentpage_.reset();
    epd_driver_.reset();
    return Result<void>::Success();
}
Result<void> EPD_Component::printrange(std::string descrstr){
    std::cout << descrstr << std::endl;
    // printComponentRange(range_);
    return Result<void>::Success();
}