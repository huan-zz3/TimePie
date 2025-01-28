#ifndef ITIMEBOOK_H
#define ITIMEBOOK_H

#include "predefine.h"
#include <map>

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
    explicit ITimeBook(void);

    virtual void timebookInit(Result<void>) = 0;
    virtual void timebookExit(Result<void>) = 0;
    /* handle in local*/
    virtual void addTimeItem(Result<void>) = 0;
    virtual void submitTimeItem(Result<void>) = 0;
    /* sync with cloud */
    virtual void pushTimeItems(Result<void>) = 0;
    virtual void pullTimeItems(Result<void>) = 0;
    /* return local data */
    virtual void getTimeItems(Result<std::map<unsigned int, timebookitem>>) = 0;

private:
    std::map<unsigned int, timebookitem> localTimebookItems;
    std::map<unsigned int, timebookitem> cloudTimebookItems;


};

#endif