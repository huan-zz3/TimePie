#ifndef IPHYSICALKEY_H
#define IPHYSICALKEY_H

#include "predefine.h"

class IPhysicalKey
{
public:
    explicit IPhysicalKey(void);

    virtual void slot_nextKey(void) = 0;
    virtual void slot_prevKey(void) = 0;
    virtual void slot_longPressNextKey(void) = 0;
    virtual void slot_longPressPrevKey(void) = 0;

public:
    Signal_void nextkeysignal_;
    Signal_void prevkeysignal_;
    Signal_void longpressnextkeysignal_;
    Signal_void longpressprevkeysignal_;

protected:
};

#endif