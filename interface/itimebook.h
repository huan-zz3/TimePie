#ifndef ITIMEBOOK_H
#define ITIMEBOOK_H

#include "i4gdtu.h"
#include "predefine.h"
#include "idatabase.h"
#include <map>
#include <memory>
#include <vector>

struct Metric
{
    int metric;
    int value;
};

struct timebookitem
{
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
    std::vector<Metric> metrics = {{0, 0}}; //上传时必选，但保持默认为空（基本用不上）
};

/*
 * 刚添加的item先通过sqlite存储，然后通过pushTimeItems()上传到服务器。
 * 本地存储除timebookitem内还需另加两个字段：_itemid、_synced。前者是本地存储区分的id，后者是标明是否已经上传到服务器。
 */
class ITimeBook
{
public:
    explicit ITimeBook(std::string _username, std::string _password) : username_(_username), password_(_password) {};

    // virtual Result<void> timebookInit() = 0;
    // virtual Result<void> timebookExit() = 0;
    virtual Result<void> setI4GDTU(std::shared_ptr<I4GDTU>) = 0;
    virtual Result<void> setIDatabase(std::shared_ptr<IDatabase>) = 0;
    virtual Result<void> timebookLogin() = 0;
    /* handle in local*/
    virtual Result<std::string> addTimeItem(int _category, std::string _date, std::string _start, std::string _end, int duration) = 0;
    /* sync with cloud */
    virtual Result<void> submitTimeItem(std::string _itemid) = 0;
    // virtual Result<void> pushTimeItems() = 0;
    // virtual Result<void> pullTimeItems() = 0;
    /* return local data */
    virtual Result<std::map<std::string, timebookitem>> getTimeItems() = 0;

public:
    // Signal_void timebook

protected:
    std::string username_, password_;
    std::string token_;
    unsigned long expire_timestamp_;

    std::shared_ptr<I4GDTU> i4gdtu_;
    std::shared_ptr<IDatabase> idatabase_;
    std::map<std::string, timebookitem> localtimebookitems_;
};

#endif