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
        std::cout << "LoginData: " << _sendata << std::endl;
        auto _rt = i4gdtu_->dtuJSONCommunication(_sendata, 5000);
        if (!_rt.isSuccess())
        {
            std::cout << _rt.errormsg() << std::endl;
            return Result<void>::Error("Login err");
        }
        json jsonData = json::parse(_rt.successvalue());
        token_ = jsonData["data"]["token"];
        expire_timestamp_ = jsonData["data"]["expire_at"];

        std::cout << "token_: " << token_ << std::endl;
        std::cout << "expire_timestamp_: " << expire_timestamp_ << std::endl;

        return Result<void>::Success();
    }
    catch (const std::exception &e)
    {
        std::cout << "JSON error: " << e.what() << std::endl;
        return Result<void>::Error("Json err");
    }
}
/* handle in local*/
Result<std::string> TimeBook::addTimeItem(int _category, std::string _date, std::string _start, std::string _end, int duration)
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

    return Result<std::string>::Success(getItemidResult.successvalue().at(0).at("last_insert_rowid()"));    // 未能测试是否正确放回itemid
}


/* sync with cloud */
Result<void> TimeBook::submitTimeItem(std::string _itemid)
{
}
/* return local data */
Result<std::map<std::string, timebookitem>> TimeBook::getTimeItems()
{
}