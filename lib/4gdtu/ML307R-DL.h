#ifndef ML307R_DL_H
#define ML307R_DL_H

// #include "i4gdtu.h"
#include "result.hpp"
#include "serialib.h"
#define SERIAL_PORT "/dev/ttyS3"
#define BAUDRATE 115200
#define INTERVAL 100          // ms
#define REST_WAITIME 1000 * 2 // ms
#define MAX_RETRY 6

#include <thread>
#include <chrono>
#include <unistd.h>
#include <mutex>

class ML307R
{
public:
    ML307R();
    ~ML307R();

    Result<void> dtuInit();
    Result<void> dtuExit();
    Result<void> dtuReset();
    Result<void> dtuIsOnline();
    /* there will be some Return value*/
    Result<std::string> dtuJSONCommunication(std::string _data, unsigned int _timeout);
    Result<std::string> dtuTIME(void);
    // Maybe there will be a function to clear the serial buffer

private:
    std::unique_ptr<serialib> serial_ptr_;
    std::mutex serial_mutex_;
    Result<std::string> dtuSendandRec(std::string data, unsigned int timeout);
    Result<std::string> dtuATRecvExtract(std::string data);
    Result<void> dtuRecvClear(void);
};

#endif // ML307R_DL_H