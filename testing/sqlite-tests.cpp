#include "catch.hpp"

#include "predefine.h"
#include "sqlite3db.h"
#include "idatabase.h"

#define SQLDB_PATH "./test.db"

TEST_CASE("sqlite 功能测试", "[uart]")
{
    std::shared_ptr<IDatabase> sqlite = std::static_pointer_cast<IDatabase>(std::make_shared<Sqlite3Database>());

    SECTION("sqlite init test")
    {
        auto _rt = sqlite->Connect(SQLDB_PATH);
        REQUIRE(_rt.isSuccess() == true);

        _rt = sqlite->disConnect();
        REQUIRE(_rt.isSuccess() == true);
    }
    SECTION("sqlite Insert test")
    {
        auto _rt = sqlite->Connect(SQLDB_PATH);
        REQUIRE(_rt.isSuccess() == true);

        // 检查表是否存在
        std::string checkTableQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name='table1';";
        auto checkTableResult = sqlite->executeQuery(checkTableQuery);
        if (!checkTableResult.isSuccess() || checkTableResult.successvalue().empty())
        {
            // 表不存在，创建新表
            std::string createTableQuery = "CREATE TABLE table1 ("
                                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                           "int1 TEXT NOT NULL, "   // 因为Insert函数实参为std::map<std::string, std::string>，所以这里int1和int2都为TEXT类型
                                           "int2 TEXT NOT NULL, "
                                           "text1 TEXT NOT NULL"
                                           ");";
            auto createTableResult = sqlite->executeNonQuery(createTableQuery);
            if (!createTableResult.isSuccess())
            {
                std::cout << createTableResult.errormsg() << std::endl;
                INFO(createTableResult.errormsg());
            }
            REQUIRE(createTableResult.isSuccess() == true);
        }

        std::map<std::string, std::string> data = {
            {"int1", "123"},
            {"int2", "456"},
            {"text1", "abcd"}
        };
        _rt = sqlite->Insert("table1", data);
        if (!_rt.isSuccess())
        {
            std::cout << _rt.errormsg() << std::endl;
        }
        REQUIRE(_rt.isSuccess() == true);

        _rt = sqlite->disConnect();
        REQUIRE(_rt.isSuccess() == true);
    }
}