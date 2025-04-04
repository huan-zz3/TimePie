#include <eventpp/eventqueue.h>
#include <iostream>
#include <string>
#include <memory>

// 事件类型定义
enum EventType {
    TemperatureEvent,
    MessageEvent
};

int main() {
    // 定义事件队列：事件类型 + void指针通用数据载体
    eventpp::EventQueue<EventType, void(EventType, const std::shared_ptr<void> &)> queue;

    // 注册温度事件监听器
    queue.appendListener(TemperatureEvent, [](EventType type, const std::shared_ptr<void> &data) {
        auto temp = *std::static_pointer_cast<const float>(data); // 使用 std::static_pointer_cast 进行类型转换
        std::cout << "温度数据: " << temp << "℃\n";
    });

    // 注册消息事件监听器
    queue.appendListener(MessageEvent, [](EventType type, const std::shared_ptr<void> &data) {
        auto msg = *std::static_pointer_cast<const std::string>(data); // 使用 std::static_pointer_cast 进行类型转换
        std::cout << "收到消息: " << msg << "\n";
    });

    // 发送温度事件
    auto tempData = std::make_shared<float>(23.5f);
    queue.enqueue(TemperatureEvent, tempData);

    // 发送消息事件
    auto msgData = std::make_shared<std::string>("系统启动完成");
    queue.enqueue(MessageEvent, msgData);

    // 处理事件队列
    queue.process();

    return 0;
}


