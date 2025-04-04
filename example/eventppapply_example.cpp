// event_types.h
// #pragma once
#include <memory>
#include <string>

enum class EventType {
    TouchInput,
    WidgetUpdate,
    LocalSave,
    TimeTick
};

// 类型关联元函数
template <EventType ET>
struct EventTraits;

template <>
struct EventTraits<EventType::TouchInput> {
    using DataType = struct {
        std::string inputType;
        int posX;
        int posY;
    };
};

template <>
struct EventTraits<EventType::WidgetUpdate> {
    using DataType = struct {
        std::string elementId;
        std::string content;
    };
};

template <>
struct EventTraits<EventType::LocalSave> {
    using DataType = struct {
        std::string path;
        std::string data;
    };
};

template <>
struct EventTraits<EventType::TimeTick> {
    using DataType = struct {
        unsigned int timestamp;
    };
};

// event_bus.h
// #pragma once
// #include "event_types.h"
#include <eventpp/eventqueue.h>

class EventBus {
public:
    template <EventType ET, typename Handler>
    void registerListener(Handler handler) {
        queue_.appendListener(ET, [handler](EventType type, const std::shared_ptr<void>& data) {
            using DataType = typename EventTraits<ET>::DataType;
            handler(*static_cast<const DataType*>(data.get()));
        });
    }

    template <EventType ET>
    void post(const typename EventTraits<ET>::DataType& data) {
        queue_.enqueue(ET, std::make_shared<typename EventTraits<ET>::DataType>(data));
    }

    void process() {
        queue_.process();
    }

private:
    eventpp::EventQueue<EventType, void(EventType, const std::shared_ptr<void>&)> queue_;
};

// main.cpp
// #include "event_bus.h"
#include <iostream>

int main() {
    EventBus bus;

    // 注册监听器（无需类型转换）
    bus.registerListener<EventType::TouchInput>([](const auto& event) {
        std::cout << "触屏输入: X=" << event.posX << " Y=" << event.posY << "\n";
    });

    bus.registerListener<EventType::WidgetUpdate>([](const auto& event) {
        std::cout << "更新控件: " << event.elementId << " 内容: " << event.content << "\n";
    });

    bus.registerListener<EventType::LocalSave>([](const auto& event) {
        std::cout << "本地保存至: " << event.path << "\n";
    });

    bus.registerListener<EventType::TimeTick>([](const auto& event) {
        std::cout << "时间戳: " << event.timestamp << "\n";
    });

    // 发送事件
    bus.post<EventType::TouchInput>({"TOUCH", 100, 200});
    bus.post<EventType::WidgetUpdate>({"statusBar", "Ready"});
    bus.post<EventType::LocalSave>({"/data/config.cfg", "auto_save=true"});
    bus.post<EventType::TimeTick>({1625097600});

    // 处理事件
    bus.process();

    return 0;
}