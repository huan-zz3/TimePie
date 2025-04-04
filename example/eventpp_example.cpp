#include <iostream>
#include <string>
#include "eventpp/eventqueue.h"
#include <thread>

int main()
{
    using EQ = eventpp::EventQueue<int, void(int)>;
    EQ queue;

    constexpr int stopEvent = 1;
    constexpr int otherEvent = 2;

    // 启动一个新线程来处理事件队列。所有监听器都会在该线程中启动运行
    std::thread thread([stopEvent, otherEvent, &queue]()
                       {
	volatile bool shouldStop = false;
    queue.appendListener(stopEvent, [&shouldStop](int) {
        shouldStop = true;
    });
    queue.appendListener(otherEvent, [](const int index) {
        std::cout << "Got event, index is " << index << std::endl;
    });
    
    while(! shouldStop) {
        queue.wait();
        
        queue.process();
    } });

    // 将一个主线程的事件加入队列。在休眠 10 ms 时，该事件应该已经被另一个线程处理了
    queue.enqueue(otherEvent, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Should have triggered event with index = 1" << std::endl;

    queue.enqueue(otherEvent, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Should have triggered event with index = 2" << std::endl;

    {
        // EventQueue::DisableQueueNotify 是一个 RAII 类，能避免唤醒其他的等待线程。
        // 所以该代码块内不会触发任何事件。
        // 当需要一次性添加很多事件，希望在事件都添加完成后才唤醒等待线程时，
        // 就可以使用 DisableQueueNotify
        EQ::DisableQueueNotify disableNotify(&queue);

        queue.enqueue(otherEvent, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Should NOT trigger event with index = 10" << std::endl;

        queue.enqueue(otherEvent, 11);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Should NOT trigger event with index = 11" << std::endl;
    }
    // DisableQueueNotify 对象在此处销毁，恢复唤醒其他的等待线程。因此事件都会在此处触发
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Should have triggered events with index = 10 and 11" << std::endl;

    queue.enqueue(stopEvent, 1);
    thread.join();
}