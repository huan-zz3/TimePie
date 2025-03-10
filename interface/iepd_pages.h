#ifndef IEPD_PAGES_H
#define IEPD__PAGES_H

#include "iepd_driver.h"
#include "predefine.h"
#include <memory>
#include <list>
#include <map>
#include <functional>

struct CompomentScale
{
    PointCoordinates startpoint;
    PointCoordinates endpoint;
};

class IEPD_Pages
{
public:
    explicit IEPD_Pages(std::shared_ptr<IEPD_Driver> _epdd) : epd_driver_(std::move(_epdd)) {};
    virtual Result<void> pageShow() = 0;
    virtual Result<void> pageRefresh() = 0;
    virtual Result<void> pageClicked(PointCoordinates) = 0;
    virtual Result<size_t> pageComponentsCount() = 0;
    virtual Result<void> pageLoadPic() = 0;

protected:
    std::shared_ptr<IEPD_Driver> epd_driver_;
    ImageBuffer_ptr image_ptr;
    std::list<std::string> compoments_list;
    std::list<std::map<std::string, CompomentScale>> compoments_scale_list;
    std::list<std::map<std::string, std::function<Result<void>(void)>>> compoments_clickslot_list;
};

#endif // IEPD_PAGES_H