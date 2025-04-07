#pragma once
#include <eventpp/eventqueue.h>
#include <typeindex>
#include <memory>
#include <functional>

class EventBus {
public:
    template <typename EventType>
    void registerListener(const std::function<void(const EventType&)>& handler) {
        auto wrapper = [handler](const std::shared_ptr<void>& data) {
            handler(*static_cast<const EventType*>(data.get()));
        };
        queue.appendListener(std::type_index(typeid(EventType)), wrapper);
    }

    template <typename EventType>
    void post(const EventType& event) {
        queue.enqueue(std::type_index(typeid(EventType)),
                      std::make_shared<EventType>(event));
    }

    void process() {
        queue.process();
    }

private:
    using KeyType = std::type_index;
    using DataType = std::shared_ptr<void>;
    using QueueType = eventpp::EventQueue<KeyType, void(const DataType&)>;
    QueueType queue;
};
