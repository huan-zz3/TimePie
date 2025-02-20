#ifndef I4GDTU_H
#define I4GDTU_H

#include "predefine.h"
#include "serialib.h"
#include <memory>

class I4GDTU
{
public:
    explicit I4GDTU(void){};

    virtual Result<void> dtuInit(std::unique_ptr<serialib>) = 0;
    virtual Result<void> dtuExit(void) = 0;
    virtual Result<void> dtuReset(void) = 0;
    virtual Result<void> dtuIsOnline(void) = 0;
    /* there may be some Return value*/
    virtual Result<std::string> dtuJSONCommunication(std::string _data, unsigned int _timeout) = 0;
    virtual Result<std::string> dtuTIME(void) = 0;
protected:
    std::unique_ptr<serialib> serial_ptr_;
    virtual Result<std::string> dtuSendandRec(std::string _data, unsigned int _timeout) = 0;

};

#endif