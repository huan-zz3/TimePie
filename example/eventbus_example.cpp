#include "eventbus/eventbus.hpp"
#include "eventbus/categories/interaction.hpp"
#include "eventbus/categories/system.hpp"
#include <iostream>

int main() {
    EventBus bus;

    // 注册监听器（按类型）
    bus.registerListener<TouchInputEvent>([](const TouchInputEvent& e) {
        std::cout << "触屏输入: X=" << e.posX << " Y=" << e.posY << " 类型: " << "\n";
    });

    bus.registerListener<LocalSaveEvent>([&bus](const LocalSaveEvent& e) {
        bus.clear();    // 在事件执行中调用clear，不会清除后续事件
        std::cout << "保存路径: " << e.path << " 数据: " << e.data << "\n";
    });

    bus.registerListener<TomatoFinish>([](const TomatoFinish& e){
        std::cout << "番茄钟结束" << "\n";
    });

    // 发送事件
    bus.post(TouchInputEvent(100, 200));
    bus.post(LocalSaveEvent("/data/config.cfg", "auto_save=true"));
    bus.post(TomatoFinish());

    // bus.clear();

    // 处理事件
    bus.process();

    return 0;
}
