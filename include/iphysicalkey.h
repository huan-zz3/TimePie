#ifndef IPHYSICALKEY_H
#define IPHYSICALKEY_H

#include "predefine.h"


class IPhysicalKey
{
public:
    explicit IPhysicalKey(void);

    virtual void nextKey(Result<void>) = 0;
    virtual void prevKey(Result<void>) = 0;
    virtual void longPressNextKey(Result<void>) = 0;
    virtual void longPressPrevKey(Result<void>) = 0;

private:

};

#endif