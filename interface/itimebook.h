#ifndef ITIMEBOOK_H
#define ITIMEBOOK_H

#include "i4gdtu.h"
#include "predefine.h"
#include <map>
#include <memory>

struct timebookitem
{
    unsigned int eventid;
    std::string starttime;
    std::string endtime;

    std::string event;
    // std::string specification;
    
    unsigned int superclass_id;
    std::string superclass_name;
    unsigned int subclass_id;
    std::string subclass_name;
};


class ITimeBook
{
public:
    explicit ITimeBook(void){};

    virtual Result<void> timebookInit() = 0;
    virtual Result<void> timebookExit() = 0;
    /* handle in local*/
    virtual Result<void> addTimeItem() = 0;
    virtual Result<void> submitTimeItem() = 0;
    /* sync with cloud */
    virtual Result<void> pushTimeItems() = 0;
    virtual Result<void> pullTimeItems() = 0;
    /* return local data */
    virtual Result<std::map<unsigned int, timebookitem>> getTimeItems() = 0;

public:
    // Signal_void timebook

protected:
    std::unique_ptr<I4GDTU> i4gdtu_;
    std::map<unsigned int, timebookitem> localtimebookitems_;
    std::map<unsigned int, timebookitem> cloudtimebookitems_;


};

#endif