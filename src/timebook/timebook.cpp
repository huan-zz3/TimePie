#include "timebook.h"

Result<void> TimeBook::setI4GDTU(std::shared_ptr<ML307R> _i4gdtu)
{
    i4gdtu_ = std::move(_i4gdtu);
    return Result<void>::Success();
}
Result<void> TimeBook::setIDatabase(std::shared_ptr<Sqlite3Database> _idatabase)
{
    idatabase_ = std::move(_idatabase);

    auto _rt = idatabase_->Connect(SQLDB_PATH);
    if (!_rt.isSuccess())
    {
        return Result<void>::Error("Database connect err");
    }

    // 检查表是否存在
    std::string checkTableQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name='timeitem';";
    auto checkTableResult = idatabase_->executeQuery(checkTableQuery);
    if (!checkTableResult.isSuccess() || checkTableResult.successvalue().empty())
    {
        // 表不存在，创建新表
        std::string createTableQuery = "CREATE TABLE timeitem ("
                                       "itemid INTEGER PRIMARY KEY AUTOINCREMENT, "
                                       "synced TEXT NOT NULL, "
                                       "category TEXT NOT NULL, "
                                       "date TEXT NOT NULL, "
                                       "starttime TEXT NOT NULL, "
                                       "endtime TEXT NOT NULL, "
                                       "duration TEXT NOT NULL, "
                                       "description TEXT, "
                                       "remark TEXT, "
                                       "weather TEXT, "
                                       "money TEXT, "
                                       "income TEXT, "
                                       "up TEXT, "
                                       "down TEXT, "
                                       "tag TEXT, "
                                       "people TEXT, "
                                       "location TEXT, "
                                       "thing TEXT, "
                                       "attachments TEXT"
                                       ");";
        auto createTableResult = idatabase_->executeNonQuery(createTableQuery);
        if (!createTableResult.isSuccess())
        {
            return Result<void>::Error("Failed to create table");
        }
    }

    return Result<void>::Success();
}

Result<void> TimeBook::timebookLogin()
{
    if (!i4gdtu_->dtuIsOnline().isSuccess())
    {
        return Result<void>::Error("dtu is not online");
    }
    json _logindata;
    _logindata["username"] = username_;
    _logindata["password"] = password_;

    try
    {
        std::string _sendata = std::string(METHOD_POST) + "||" + std::string(URL_LOGIN) + "||||" + _logindata.dump();
        LOG(INFO) << "LoginData: " << _sendata << std::endl;
        auto _rt = i4gdtu_->dtuJSONCommunication(_sendata, 5000);
        if (!_rt.isSuccess())
        {
            LOG(ERROR) << _rt.errormsg() << std::endl;
            return Result<void>::Error("Login err");
        }
        json jsonData = json::parse(_rt.successvalue());
        token_ = jsonData["data"]["token"];
        expire_timestamp_ = jsonData["data"]["expire_at"];

        LOG(INFO) << "token_: " << token_ << std::endl;
        LOG(INFO) << "expire_timestamp_: " << expire_timestamp_ << std::endl;

        return Result<void>::Success();
    }
    catch (const std::exception &e)
    {
        LOG(ERROR) << "JSON error: " << e.what() << std::endl;
        return Result<void>::Error("Json err");
    }
}
/* handle in local*/
Result<std::string> TimeBook::addTimeItem(int _category, std::string _date, std::string _start, std::string _end, uint32_t duration)
{
    // 创建一个新的 timebookitem 实例
    timebookitem newItem;
    newItem.category = _category;
    newItem.date = _date;
    newItem.starttime = _start;
    newItem.endtime = _end;
    newItem.duration = duration;
    bool synced = false; // 默认为 false

    // 将 newItem 插入到数据库中
    std::map<std::string, std::string> data = {
        {"synced", synced ? "1" : "0"},
        {"category", std::to_string(newItem.category)},
        {"date", newItem.date},
        {"starttime", newItem.starttime},
        {"endtime", newItem.endtime},
        {"duration", std::to_string(newItem.duration)},
        // 其他字段可以根据需要添加
    };
    auto _rt = idatabase_->Insert("timeitem", data);
    if (!_rt.isSuccess())
    {
        return Result<std::string>::Error("Failed to insert item");
    }

    // 从数据库中获取新插入的 itemid
    std::string getItemidQuery = "SELECT last_insert_rowid();";
    auto getItemidResult = idatabase_->executeQuery(getItemidQuery);
    if (!getItemidResult.isSuccess() || getItemidResult.successvalue().empty())
    {
        return Result<std::string>::Error("Failed to get itemid");
    }

    return Result<std::string>::Success(getItemidResult.successvalue().at(0).at("last_insert_rowid()")); // 未能测试是否正确放回itemid
}

/* sync with cloud */
Result<void> TimeBook::submitTimeItem(std::string _itemid)
{
    // 从数据库中获取所有synced值为0的数据
    std::string query = "SELECT * FROM timeitem WHERE synced = 0;";
    auto result = idatabase_->executeQuery(query);
    if (!result.isSuccess())
    {
        return Result<void>::Error("Failed to get unsynced time items");
    }

    // 遍历未同步的数据
    for (const auto &row : result.successvalue())
    {
        json jsonData;
        jsonData["id"] = row.at("itemid");
        jsonData["category"] = std::stoi(row.at("category"));
        jsonData["date"] = row.at("date");
        jsonData["start"] = row.at("starttime");
        jsonData["end"] = row.at("endtime");
        jsonData["duration"] = std::stoi(row.at("duration"));
        jsonData["metrics"] = json::array();                          // 初始化为空数组
        jsonData["metrics"].push_back({{"metric", 0}, {"value", 0}}); // 添加示例metric
        // 其他字段可以根据需要添加

        std::string _sendata = std::string(METHOD_POST) + "||" + std::string(URL_SAVERECORD) + "||" + token_ + "||" + jsonData.dump();
        LOG(INFO) << "SubmitData: " << _sendata << std::endl;

        // 通过dtu提交数据
        auto _rt = i4gdtu_->dtuJSONCommunication(_sendata, 5000);
        if (!_rt.isSuccess())
        {
            LOG(ERROR) << _rt.errormsg() << std::endl;
            return Result<void>::Error("Failed to submit time item");
        }
        LOG(INFO) << "submitTimeItem: " << _rt.successvalue() << std::endl;

        // 判断提交是否成功
        std::string successValue = _rt.successvalue();
        try
        {
            auto parsedJson = json::parse(successValue);

            // 检查 "code" 字段的值
            if (parsedJson.contains("code") && parsedJson["code"] == 0)
            {
                LOG(INFO) << "submitTimeItem: Success - " << parsedJson.dump(4) << std::endl;
                // 此处不返回，继续以下数据库同步操作
            }
            else
            {
                LOG(ERROR) << "submitTimeItem: Failed - " << parsedJson.dump(4) << std::endl;
                return Result<void>::Error("Failed to submit time item due to non-zero code");
            }
        }
        catch (json::parse_error &e)
        {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
            return Result<void>::Error("JSON parse error");
        }

        // 更新数据库中已提交的数据的synced值为1
        std::map<std::string, std::string> data = {
            {"synced", "1"},
        };
        auto updateResult = idatabase_->Update("timeitem", data, "itemid = " + row.at("itemid"));
        if (!updateResult.isSuccess())
        {
            return Result<void>::Error("Failed to update synced status");
        }
    }

    return Result<void>::Success();
}

/* return local data */
Result<std::map<std::string, timebookitem>> TimeBook::getTimeItems()
{
    std::string query = "SELECT * FROM timeitem;";
    auto result = idatabase_->executeQuery(query);
    if (!result.isSuccess())
    {
        return Result<std::map<std::string, timebookitem>>::Error("Failed to get time items");
    }

    std::map<std::string, timebookitem> timeItems;
    for (const auto &row : result.successvalue())
    {
        timebookitem item;
        item.synced = (row.at("synced") == "1");
        item.category = std::stoi(row.at("category"));
        item.date = row.at("date");
        item.starttime = row.at("starttime");
        item.endtime = row.at("endtime");
        item.duration = std::stoi(row.at("duration"));

        timeItems[item.id] = item;
    }

    for (const auto &pair : timeItems)
    {
        LOG(INFO) << "Synced: " << pair.second.synced << std::endl;
        LOG(INFO) << "Item category: " << pair.second.category << "||" << "Item date: " << pair.second.date << "||" << "Item starttime: " << pair.second.starttime << "||" << "Item endtime: " << pair.second.endtime << "||" << "Item duration: " << pair.second.duration << std::endl;
        LOG(INFO) << "-----------------------------" << std::endl;
    }

    return Result<std::map<std::string, timebookitem>>::Success(timeItems);
}
