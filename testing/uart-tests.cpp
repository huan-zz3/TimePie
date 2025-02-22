#include "catch.hpp"

#include "i4gdtu.h"
#include "ML307R-DL.h"
#include "predefine.h"
#include "serialib.h"

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

TEST_CASE("dtu收发测试", "[uart]")
{
    std::shared_ptr<I4GDTU> dtu = std::static_pointer_cast<I4GDTU>(std::make_shared<ML307R>());
    auto serial = std::make_unique<serialib>();

    SECTION("dtuInit test")
    {
        auto _rt = dtu->dtuInit(std::move(serial));
        
        REQUIRE(_rt.isSuccess() == true);

        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }
        dtu->dtuExit();
    }
    SECTION("dtuReset test")
    {
        auto _rt = dtu->dtuInit(std::move(serial));
        REQUIRE(_rt.isSuccess() == true);

        _rt = dtu->dtuReset();
        REQUIRE(_rt.isSuccess() == true);

        dtu->dtuExit();
    }
    SECTION("dtuIsOnline test")
    {
        auto _rt = dtu->dtuInit(std::move(serial));
        REQUIRE(_rt.isSuccess() == true);

        _rt = dtu->dtuIsOnline();
        REQUIRE(_rt.isSuccess() == true);

        dtu->dtuExit();
    }
    SECTION("dtuTIME test")
    {
        auto _rt = dtu->dtuInit(std::move(serial));
        REQUIRE(_rt.isSuccess() == true);

        auto _rt2 = dtu->dtuTIME();
        REQUIRE(_rt2.isSuccess() == true);
        if (_rt2.isSuccess() == false)
        {
            CAPTURE(_rt2.errormsg());
        }
        REQUIRE(_rt2.successvalue() != "");
        CAPTURE(_rt2.successvalue());

        dtu->dtuExit();
    }
    SECTION("dtuJSONCommunication test")
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));   // wait for dtu fully reset

        auto _rt = dtu->dtuInit(std::move(serial));
        REQUIRE(_rt.isSuccess() == true);

        std::string str = "GET||/api/mytime/time_record/options/||x-token:eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MSwiZXhwaXJlX2F0IjoxNzQyMDk2NDgyfQ.t1oWcoyMDl349lzplRTFGCIngTnmIkViu-Mqg0DFnDI||";

        auto _rt2 = dtu->dtuJSONCommunication(str, 2000);
        REQUIRE(_rt2.isSuccess() == true);
        if (_rt2.isSuccess() == false)
        {
            INFO(_rt2.errormsg());
        }
        REQUIRE(_rt2.successvalue() != "");
        CAPTURE(_rt2.successvalue());

        dtu->dtuExit();
    }
}

// class UniqueTestsFixture
// {
// protected:
//     UniqueTestsFixture()
//     {
//         dtu = std::make_unique<ML307R>();
//     }

//     int getID()
//     {
//         return ++uniqueID;
//     }

// protected:
//     std::unique_ptr<ML307R> dtu;

// private:
//     static int uniqueID;
// };

// TEST_CASE_METHOD(UniqueTestsFixture, "dtuInit test", "[uart]")
// {
//     auto serial = std::make_unique<serialib>();
//     auto _rt = dtu->dtuInit(std::move(serial));

//     REQUIRE(_rt.isSuccess() == true);

//     dtu->dtuExit();
// }

// TEST_CASE_METHOD(UniqueTestsFixture, "", "[uart]")
// {
//     auto serial = std::make_unique<serialib>();
//     auto _rt = dtu->dtuInit(std::move(serial));

//     REQUIRE(_rt.isSuccess() == true);


// }