#include "timebook.h"

Result<void> TimeBook::setI4GDTU(std::unique_ptr<I4GDTU> _i4gdtu)
{
    i4gdtu_ = std::move(_i4gdtu);
    return Result<void>::Success();
}
Result<void> TimeBook::timebookLogin()
{
    if(!i4gdtu_->dtuIsOnline().isSuccess()){
        return Result<void>::Error("dtu is not online");
    }
    json _logindata;
    _logindata["username"] = username_;
    _logindata["password"] = password_;
    std::cout << "LoginData: " << _logindata.dump() << std::endl;

    auto _rt = i4gdtu_->dtuSendandRec(_logindata.dump(), 5000);
    if(!_rt.isSuccess()){
        std::cout << _rt.errormsg() << std::endl;
        return Result<void>::Error("dtu send and rec error");
    }
    
    
}
/* handle in local*/
Result<std::string> TimeBook::addTimeItem(int _category, std::string _date, std::string _start, std::string _end, int duration)
{
}
/* sync with cloud */
Result<void> TimeBook::submitTimeItem(std::string _itemid)
{
}
/* return local data */
Result<std::map<std::string, timebookitem>> TimeBook::getTimeItems()
{
}