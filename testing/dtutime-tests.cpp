#include "catch.hpp"

#include "predefine.h"
#include "ML307R-DL.h"
#include "dtutime.h"

#include <thread>
#include <chrono>

std::ostream& operator<<(std::ostream& os, const timedata& time) {
    os << time.year << "-" << time.month << "-" << time.day << " "
       << time.hour << ":" << time.minute << ":" << time.second << "."
       << time.millisecond << " (" << time.timestamp << ")";
    return os;
}

TEST_CASE("dtu收发测试", "[dtutime]")
{
    std::shared_ptr<I4GDTU> dtu = std::static_pointer_cast<I4GDTU>(std::make_shared<ML307R>());
    std::shared_ptr<IInternetTime> dtutime = std::static_pointer_cast<IInternetTime>(std::make_shared<DTUTime>(dtu));
    auto serial = std::make_unique<serialib>();

    

    SECTION("setI4GDTU test")
    {
        auto _rt = dtu->dtuInit(std::move(serial));
        std::this_thread::sleep_for(std::chrono::seconds(12));   // wait for dtu fully freshing updateNowTime
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }

        auto _rt2 = dtutime->getNowTime();
        REQUIRE(_rt.isSuccess() == true);
        if (_rt.isSuccess() == false)
        {
            INFO(_rt.errormsg());
        }
        INFO(_rt2.successvalue());
        std::cout << _rt2.successvalue() << std::endl;

        dtu->dtuExit();
    }
}