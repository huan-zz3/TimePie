#pragma once

#include <memory>
#include <cstdlib>

#include "devicelayer.h"
#include "bgservice/servicelayer.h"
#include "timebook/timebook.h"

#define TIMEPIE_ACCOUNT "TIMEPIE_ACCOUNT"
#define TIMEPIE_PASSWORD "TIMEPIE_PASSWORD"

class SystemInitializer {
public:
    struct Services {
        std::shared_ptr<DeviceLayer> device;
        std::shared_ptr<ML307R> dtu;
        std::shared_ptr<DTUTime> dtuTime;
        std::shared_ptr<ServiceLayer> service;
        std::shared_ptr<TimeBook> timebook;
        // 其他服务...
    };

    static Services initialize() {
        Services s;

        // 阶段1：基础硬件初始化
        s.device = std::make_shared<DeviceLayer>();
        s.device->epdriver_Init(InitMode::Hardware);

        // 阶段2：通信模块初始化
        s.dtu = std::make_shared<ML307R>();
        if (!s.dtu->dtuInit().isSuccess()) {
            throw std::runtime_error("DTU初始化失败");
        }

        // 阶段3：依赖DTU的服务
        std::this_thread::sleep_for(std::chrono::seconds(2));
        s.dtuTime = std::make_shared<DTUTime>(s.dtu);

        // 阶段4：上层服务
        s.service = std::make_shared<ServiceLayer>(s.dtuTime);
        s.service->epdserInit();

        // 从环境变量中获取账号和密码
        const char *account_env = std::getenv(TIMEPIE_ACCOUNT);
        const char *password_env = std::getenv(TIMEPIE_PASSWORD);

        if (!account_env || !password_env) {
            LOG(ERROR) << "环境变量TIMEPIE_ACCOUNT或TIMEPIE_PASSWORD未设置" << std::endl;
            throw std::runtime_error("环境变量TIMEPIE_ACCOUNT或TIMEPIE_PASSWORD未设置");
        }

        std::string account(account_env);
        std::string password(password_env);

        // 阶段5：初始化timebook模块
        s.timebook = std::make_shared<TimeBook>(account, password);
        s.timebook->setI4GDTU(s.dtu);
        std::shared_ptr<Sqlite3Database> database = std::make_shared<Sqlite3Database>();
        s.timebook->setIDatabase(database);
        auto thread_for_timebook = std::thread([&s]() {
            while (!s.timebook->timebookLogin().isSuccess()) {
                static uint32_t count = 1;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                LOG(INFO) << "timebook login failed, retrying..." << count++ << std::endl;
            }
            LOG(INFO) << "timebook login success" << std::endl;
        });
        thread_for_timebook.detach();

        return s;
    }
};