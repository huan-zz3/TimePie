#pragma once

#include <memory>

#include "devicelayer.h"
#include "bgservice/servicelayer.h"
#include "timebook/timebook.h"
#define ACCOUNT "2805033624@qq.com"
#define PASSWORD "whl003388"

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
    
            // 阶段5：初始化timebook模块
            s.timebook = std::make_shared<TimeBook>(ACCOUNT, PASSWORD);
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