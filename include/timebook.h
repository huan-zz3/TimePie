#ifndef TIMEBOOK_H
#define TIMEBOOK_H

#include "itimebook.h"
#include "json.hpp"
using json = nlohmann::json;
// #include "ML307R-DL.h"

class TimeBook : public ITimeBook
{
public:
    TimeBook(std::string _username, std::string _password) : ITimeBook(_username, _password) {};
    ~TimeBook();

    Result<void> setI4GDTU(std::shared_ptr<I4GDTU>);
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
    using ITimeBook::localtimebookitems_;

    Result<std::string> composeJsonRequest(std::string _method, std::string _token, std::string _body);
    
};

#endif