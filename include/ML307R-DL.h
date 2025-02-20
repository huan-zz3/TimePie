#ifndef ML307R_DL_H
#define ML307R_DL_H

#include "i4gdtu.h"
#include "predefine.h"
#include "serialib.h"
#define SERIAL_PORT "/dev/ttyS3"
#define BAUDRATE 115200
#define INTERVAL 100          // ms
#define MAX_WAITIME 1000 * 10 // ms
#define MAX_RETRY 3

#include <thread>
#include <chrono>
#include <unistd.h>

class ML307R : I4GDTU
{
public:
    ML307R() {};
    ~ML307R();

    Result<void> dtuInit(std::unique_ptr<serialib> _serial_ptr);
    Result<void> dtuExit();
    Result<void> dtuReset();
    Result<void> dtuIsOnline();
    /* there may be some Return value*/
    Result<std::string> dtuSendandRec(std::string data, unsigned int timeout);
    Result<std::string> dtuNTP(void);

private:
    using I4GDTU::serial_ptr;

    Result<std::string> dtuRecvExtract(std::string data);
};

#endif // ML307R_DL_H