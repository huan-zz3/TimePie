#include "catch.hpp"

#include "predefine.h"
#include "itimebook.h"
#include "timebook.h"
#include "ML307R-DL.h"
#include "idatabase.h"
#include "sqlite3db.h"

#define ACCOUNT "2805033624@qq.com"
#define PASSWORD "whl003388"

TEST_CASE("dtu收发测试", "[uart]")
{
    std::shared_ptr<I4GDTU> dtu = std::static_pointer_cast<I4GDTU>(std::make_shared<ML307R>());
    std::shared_ptr<ITimeBook> timebook = std::static_pointer_cast<ITimeBook>(std::make_shared<TimeBook>(ACCOUNT, PASSWORD));
    auto serial = std::make_unique<serialib>();
    std::shared_ptr<IDatabase> database = std::static_pointer_cast<IDatabase>(std::make_shared<Sqlite3Database>());

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
    SECTION("timebook additem test"){
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

        _rt = timebook->setIDatabase(std::move(database));
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        auto _rt2 = timebook->addTimeItem( 1, "std::string _date", "std::string _start", "std::string _end", 66);
        REQUIRE(_rt2.isSuccess() == true);
        if (_rt2.isSuccess() == false)
        {
            INFO(_rt2.errormsg());
        }else{
            std::cout << _rt2.successvalue() << std::endl;
        }

        // dtu->dtuExit();
        timebook.reset();
    }
}