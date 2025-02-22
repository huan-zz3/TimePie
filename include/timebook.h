#ifndef TIMEBOOK_H
#define TIMEBOOK_H

#include "itimebook.h"
#include "json.hpp"
using json = nlohmann::json;

#define METHOD_POST "POST"
#define METHOD_GET "GET"
#define URL_LOGIN "/api/unibackend/login/"
#define URL_SAVERECORD "/api/mytime/time_record/detail/"

class TimeBook : public ITimeBook
{
public:
    TimeBook(std::string _username, std::string _password) : ITimeBook(_username, _password) {};
    ~TimeBook(){std::cout<< "TimeBook instance is deleted now." << std::endl;};

    Result<void> setI4GDTU(std::shared_ptr<I4GDTU>);
    Result<void> setIDatabase(std::shared_ptr<IDatabase>);
    Result<void> timebookLogin();
    /* handle in local*/
    Result<std::string> addTimeItem(int _category, std::string _date, std::string _start, std::string _end, int duration);
    /* sync with cloud */
    Result<void> submitTimeItem(std::string _itemid);
    /* return local data */
    Result<std::map<std::string, timebookitem>> getTimeItems();

private:
    using ITimeBook::username_;
    using ITimeBook::password_;
    using ITimeBook::token_;

    using ITimeBook::expire_timestamp_;
    using ITimeBook::i4gdtu_;
    using ITimeBook::idatabase_;
    using ITimeBook::localtimebookitems_;

    Result<std::string> composeJsonRequest(std::string _method, std::string _token, std::string _body);
    
};

#endif