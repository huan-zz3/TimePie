#include "catch.hpp"

#include "predefine.h"
#include "itimebook.h"
#include "timebook.h"
#include "ML307R-DL.h"

#define ACCOUNT "2805033624@qq.com"
#define PASSWORD "whl003388"

TEST_CASE("dtu收发测试", "[uart]")
{
    std::shared_ptr<I4GDTU> dtu = std::static_pointer_cast<I4GDTU>(std::make_shared<ML307R>());
    std::shared_ptr<ITimeBook> timebook = std::static_pointer_cast<ITimeBook>(std::make_shared<TimeBook>(ACCOUNT, PASSWORD));
    auto serial = std::make_unique<serialib>();

    SECTION("setI4GDTU test")
    {
        auto _rt = dtu->dtuInit(std::move(serial));
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        _rt = timebook->setI4GDTU(std::move(dtu));
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        // dtu->dtuExit();
        timebook.reset();
    }
    SECTION("timebook login test"){
        auto _rt = dtu->dtuInit(std::move(serial));
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        _rt = timebook->setI4GDTU(std::move(dtu));
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        _rt = timebook->timebookLogin();
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        // dtu->dtuExit();
        timebook.reset();
    }
}