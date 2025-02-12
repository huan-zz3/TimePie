#ifndef I4GDTU_H
#define I4GDTU_H

#include "predefine.h"

class I4GDTU
{
public:
    explicit I4GDTU(void){};

    virtual Result<void> dtuInit() = 0;
    virtual Result<void> dtuEnit() = 0;
    /* there may be some Return value, wo should improve later */
    virtual Result<std::string> httpPost(std::string URL_API) = 0;
    virtual Result<std::string> httpGet(std::string URL_API) = 0;

protected:


};

#endif