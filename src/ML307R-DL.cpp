#include "ML307R-DL.h"

ML307R::~ML307R()
{
    dtuExit();
}

Result<void> ML307R::dtuInit(std::unique_ptr<serialib> _serial_ptr)
{
    serial_ptr_ = std::move(_serial_ptr);
    // 打开串口设备
    char errorOpening = serial_ptr_->openDevice(SERIAL_PORT, BAUDRATE);
    if (errorOpening == '1')
    {
        return Result<void>::Success();
    }
    else
    {
        return Result<void>::Error("Error Code: " + errorOpening);
    }
}
Result<void> ML307R::dtuExit()
{
    serial_ptr_->closeDevice();
    serial_ptr_.reset();
}
Result<void> ML307R::dtuReset()
{
    // 发送AT+REST指令重启DTU
    Result<std::string> result = dtuSendandRec("AT+REST", MAX_WAITIME);
    if (result.isSuccess())
    {
        std::cout << "DTU重启指令已发送，开始等待重启..." << std::endl;

        int retryCount = 0;

        // 在发送重启指令后，先等待至少5秒
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // 尝试重新连接并检查DTU是否已重启
        while (retryCount < MAX_RETRY)
        {
            // 尝试发送一个简单的AT指令
            result = dtuSendandRec("AT", 2000);
            if (result.isSuccess() && result.successvalue().find("OK") != std::string::npos)
            {
                std::cout << "DTU已成功重启并响应。" << std::endl;
                return Result<void>::Success();
            }
            else
            {
                std::cout << "检测到DTU未响应，等待1秒后重试..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                retryCount++;
            }
        }

        // 所有重试失败后，返回错误
        return Result<void>::Error("DTU重启失败或未能在预期时间内响应。");
    }
    else
    {
        return Result<void>::Error("发送AT+REST指令失败。");
    }
}

Result<void> ML307R::dtuIsOnline()
{
    // 发送AT+CEREG?指令监测DTU是否驻网
    Result<std::string> result = dtuSendandRec("AT+CEREG?", 1000);
    if (result.isSuccess())
    {
        std::cout << "DTU查询驻网指令发送成功" << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        // auto _rt = dtuATRecvExtract(result.successvalue());  // 无需提取，直接判断
        if (result.successvalue().find("1") != std::string::npos || result.successvalue().find("5") != std::string::npos)
        {
            return Result<void>::Success();
        }
        return Result<void>::Error("DTU不在驻网状态");
    }
    else
    {
        return Result<void>::Error("发送AT+CEREG?指令失败。");
    }
}
/* there may be some Return value*/
Result<std::string> ML307R::dtuTIME(void)
{
    // 发送AT+TIME指令查询DTU设备网路时间，请务必确保设备已驻网
    Result<std::string> result = dtuSendandRec("AT+TIME", 1000);
    if (result.isSuccess())
    {
        std::cout << "查询DTU设备网路时间指令发送成功" << std::endl;
        auto _rt = dtuATRecvExtract(result.successvalue());
        if (_rt.isSuccess())
        {
            return Result<std::string>::Success(_rt.successvalue());
        }
        else
        {
            std::cout << "Failed to extract data: " << _rt.errormsg() << std::endl;
            return Result<std::string>::Error("No data received");
        }
        return Result<std::string>::Success(std::move(result.successvalue()));
    }
    else
    {
        return Result<std::string>::Error("发送AT+TIME指令失败。");
    }
}
Result<std::string> ML307R::dtuSendandRec(std::string _data, unsigned int _timeout)
{
    // 发送数据
    if (serial_ptr_->writeString(_data.c_str()) != 1)
    {
        return Result<std::string>::Error("Failed to send data");
    }

    // 初始化缓冲区和接收数据的总超时时间
    char buffer[512] = {0};
    std::string receivedData = "";
    // unsigned int total_timeout = timeout;

    // 循环接收数据，直到接收到所有数据部分或超时
    unsigned int interval = 0;
    while (true)
    {
        // 每次读取数据，使用较小的超时以避免长时间阻塞
        // unsigned int read_timeout = 200; // 每次读取的超时时间200ms
        // if (total_timeout <= 0)
        // {
        //     break; // 总超时已到，不再继续接收
        // }

        // 计算剩余总超时时间
        // total_timeout = (total_timeout < read_timeout) ? 0 : total_timeout - read_timeout;

        // 从串口读取数据到缓冲区，直到换行符或超时
        int bytesRead = serial_ptr_->readString(buffer, '\n', sizeof(buffer) - 1, _timeout); // old read_timeout

        // 处理读取结果
        switch (bytesRead)
        {
        case -1:
            return Result<std::string>::Error("Error while setting the Timeout");
        case -2:
            return Result<std::string>::Error("Error while reading the character");
        case -3:
            return Result<std::string>::Error("MaxNbBytes reached");
        case 0:
            // 未接收到任何数据，判定为数据接收完毕，退出循环
            // std::cout << "Timeout while reading, remained time:" << total_timeout << std::endl;
            std::cout << "Timeout while reading" << std::endl;
            break;
        default:
            // if (bytesRead > 0)
            // {
            // 将读取到的数据拼接到receivedData中
            std::this_thread::sleep_for(std::chrono::milliseconds(INTERVAL));
            receivedData += std::string(buffer, bytesRead);
            // }
            // 检查是否已经读取到换行符，即数据部分结束
            // if (buffer[bytesRead - 1] == '\n')
            // {
            //     break; // 已读取到完整的一部分，跳出循环
            // }
            // 间隔200ms，等待下一部分数据
            // usleep(INTERVAL * 1000); // usleep的时间单位为微秒，x ms = x * 1000 us
        }
    }

    // 返回接收到的数据
    std::cout << "Received data: " << receivedData << std::endl;
    return Result<std::string>::Success(receivedData);
    // auto _rt = dtuRecvExtract(receivedData);
    // if (_rt.isSuccess())
    // {
    //     return Result<std::string>::Success(_rt.successvalue());
    // }
    // else
    // {
    //     std::cout << "Failed to extract data: "<< _rt.errormsg() << std::endl;
    //     return Result<std::string>::Error("No data received");
    // }
}
Result<std::string> ML307R::dtuATRecvExtract(const std::string input)
{
    size_t start_pos = input.find('"');
    if (start_pos == std::string::npos)
    {
        return Result<std::string>::Error("No quoted string found" + input);
    }
    size_t end_pos = input.find('"', start_pos + 1);
    if (end_pos == std::string::npos)
    {
        return Result<std::string>::Error("No closing quote found" + input);
    }
    return Result<std::string>::Success(input.substr(start_pos + 1, end_pos - start_pos - 1));
}
Result<std::string> ML307R::dtuJSONCommunication(std::string _data, unsigned int _timeout)
{
    auto result = dtuSendandRec(_data, _timeout);
    if (!result.isSuccess())
    {
        return Result<std::string>::Error("Failed to send data: " + result.errormsg());
    }
    auto _rt = result.successvalue();
    size_t start_pos = _rt.find('{');
    size_t end_pos = _rt.find_last_of('}');
    if( start_pos == std::string::npos || end_pos == std::string::npos)
    {
        return Result<std::string>::Error("No {} data found");
    }
    return Result<std::string>::Success(_rt.substr(start_pos, end_pos - start_pos + 1));
}