#include "timebook.h"

Result<void> TimeBook::setI4GDTU(std::shared_ptr<I4GDTU> _i4gdtu)
{
    i4gdtu_ = std::move(_i4gdtu);
    return Result<void>::Success();
}
Result<void> TimeBook::setIDatabase(std::shared_ptr<IDatabase> _idatabase){
    idatabase_ = std::move(_idatabase);
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
        std::string _sendata = std::string(METHOD_POST) + "||" + std::string(URL_LOGIN) + "||||" +  _logindata.dump();
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
}
/* sync with cloud */
Result<void> TimeBook::submitTimeItem(std::string _itemid)
{
}
/* return local data */
Result<std::map<std::string, timebookitem>> TimeBook::getTimeItems()
{
}