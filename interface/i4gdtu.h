#ifndef I4GDTU_H
#define I4GDTU_H

#include "predefine.h"

class I4GDTU
{
public:
    explicit I4GDTU(void);

    virtual void dtuInit(Result<void>) = 0;
    virtual void dtuEnit(Result<void>) = 0;
    /* there may be some Return value, wo should improve later */
    virtual void httpPost(Result<std::string>, std::string URL_API) = 0;
    virtual void httpGet(Result<std::string>, std::string URL_API) = 0;

protected:


};

#endif