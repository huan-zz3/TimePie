#include "catch.hpp"

#include "predefine.h"
#include "timebook/timebook.h"
#include "ML307R-DL.h"
#include "sqlite3db.h"

#define ACCOUNT "2805033624@qq.com"
#define PASSWORD "whl003388"

TEST_CASE("dtu收发测试", "[uart]")
{
    std::shared_ptr<ML307R> dtu = std::static_pointer_cast<ML307R>(std::make_shared<ML307R>());
    std::shared_ptr<TimeBook> timebook = std::static_pointer_cast<TimeBook>(std::make_shared<TimeBook>(ACCOUNT, PASSWORD));
    // auto serial = std::make_unique<serialib>();
    std::shared_ptr<Sqlite3Database> database = std::static_pointer_cast<Sqlite3Database>(std::make_shared<Sqlite3Database>());

    // SECTION("setI4GDTU test")
    // {
    //     auto _rt = dtu->dtuInit();
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     _rt = timebook->setI4GDTU(std::move(dtu));
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     // dtu->dtuExit();
    //     timebook.reset();
    // }
    // SECTION("timebook login test"){
    //     auto _rt = dtu->dtuInit();
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     _rt = timebook->setI4GDTU(std::move(dtu));
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     _rt = timebook->timebookLogin();
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     // dtu->dtuExit();
    //     timebook.reset();
    // }
    // SECTION("timebook additem test"){
    //     auto _rt = dtu->dtuInit();
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     _rt = timebook->setI4GDTU(std::move(dtu));
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     _rt = timebook->setIDatabase(std::move(database));
    //     REQUIRE(_rt.isSuccess() == true);
    //     if (_rt.isSuccess() == false)
    //     {
    //         INFO(_rt.errormsg());
    //     }

    //     auto _rt2 = timebook->addTimeItem( 1, "std::string _date", "std::string _start", "std::string _end", 66);
    //     REQUIRE(_rt2.isSuccess() == true);
    //     if (_rt2.isSuccess() == false)
    //     {
    //         INFO(_rt2.errormsg());
    //     }else{
    //         std::cout << _rt2.successvalue() << std::endl;
    //     }

    //     // dtu->dtuExit();
    //     timebook.reset();
    // }
    SECTION("timebook getitem test")
    {
        auto _rt = dtu->dtuInit();
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

        _rt = timebook->setIDatabase(std::move(database));
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        auto _rt2 = timebook->getTimeItems();
        REQUIRE(_rt2.isSuccess() == true);

        auto _rt3 = timebook->submitTimeItem("nothing");
        REQUIRE(_rt3.isSuccess() == true);
    }
}