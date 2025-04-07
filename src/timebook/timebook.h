#ifndef TIMEBOOK_H
#define TIMEBOOK_H

// #include "itimebook.h"
#include "ML307R-DL.h"
#include "sqlite3db.h"

#include "json.hpp"
using json = nlohmann::json;

#define METHOD_POST "POST"
#define METHOD_GET "GET"
#define URL_LOGIN "/api/unibackend/login/"
#define URL_SAVERECORD "/api/mytime/time_record/detail/"
#define SQLDB_PATH "./timeitem.db"

struct Metric
{
    int metric;
    int value;
};

struct timebookitem
{
    bool synced = false;

    std::string id = "";
    int category;
    std::string date;
    std::string starttime;
    std::string endtime;
    int duration;
    std::string description = "";
    std::string remark = "";
    std::string weather = "";
    int money = 0;
    int income = 0;
    std::string up = "";
    std::string down = "";
    std::string tag = "";
    std::string people = "";
    std::string location = "";
    std::string thing = "";
    std::string attachments = "";
    std::vector<Metric> metrics = {{0, 0}}; // 上传时必选，但保持默认为空（基本用不上）
};

class TimeBook
{
public:
    TimeBook(std::string _username, std::string _password) : username_(_username), password_(_password) {};
    ~TimeBook() { std::cout << "TimeBook instance is deleted now." << std::endl; };

    Result<void> setI4GDTU(std::shared_ptr<ML307R>);
    Result<void> setIDatabase(std::shared_ptr<Sqlite3Database>);
    Result<void> timebookLogin();
    /* handle in local*/
    Result<std::string> addTimeItem(int _category, std::string _date, std::string _start, std::string _end, int duration);
    /* sync with cloud */
    Result<void> submitTimeItem(std::string _itemid);
    /* return local data */
    Result<std::map<std::string, timebookitem>> getTimeItems();

private:
    std::string username_, password_;
    std::string token_;
    unsigned long expire_timestamp_;

    std::shared_ptr<ML307R> i4gdtu_;
    std::shared_ptr<Sqlite3Database> idatabase_;
    std::map<std::string, timebookitem> localtimebookitems_;

    // Result<std::string> composeJsonRequest(std::string _method, std::string _token, std::string _body);
};

#endif