#ifndef EPD_COMPOMENT_H
#define EPD_COMPOMENT_H

#include "predefine.h"
#include "iepd_driver.h"
#include "epd_pages.h"
#include <memory>
#include <map>
#include <vector>

using ComponentRange = std::list<std::vector<PointCoordinates>>;
class EPD_Page;
class EPD_Component : public std::enable_shared_from_this<EPD_Component>
{
public:
    explicit EPD_Component(std::shared_ptr<IEPD_Driver>);
    ~EPD_Component();
    virtual Result<void> draw() = 0;
    Signal_void signal_clicked_;

    Result<void> setstartcordinate(PointCoordinates);
    Result<void> setparentpage(std::shared_ptr<EPD_Page>);
    Result<void> setvisable(bool);
    Result<bool> getvisable();
    Result<void> printrange(std::string);

private:
    Result<void> delete_remove();

protected:
    std::shared_ptr<EPD_Page> parentpage_;
    PointCoordinates startcordinate_ = {999, 999};
    ComponentRange range_ = {{{0, 0}}};
    bool visible_ = true;

    std::shared_ptr<IEPD_Driver> epd_driver_;
};

#endif // EPD_COMPOMENT_H