#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <functional>

#include "Events.hpp"


class EventDispatcher {
public:
    EventDispatcher() : running(true), eventThread(&EventDispatcher::processEvents, this) {}

    ~EventDispatcher();

public:
    // Add listener with a unique key for fine-grained control
    template<typename T, typename EventClass, typename... Args>
    void addListener(EventType type, const std::string& eventName, void (T::* memberFunc)(EventClass&, Args...), T* instance, Args... args) {
        listeners[type][eventName] = [=](EventBase& event)
            {
                if (auto* specificEvent = static_cast<EventClass*>(&event))
                    (instance->*memberFunc)(*specificEvent, args...);
            };
    }

    // Dispatch an event to be processed in the event bus
    void dispatch(EventType type, EventBase& event, const std::string& listenerKey, bool highPriority = false);
private:
    // Process events with priority and round-robin scheduling
    void processEvents();

    // Execute all listeners for a specific event type
    void executeListeners(EventType type, EventBase& event);

private:
    // Map EventType and a string key to specific listeners
    std::unordered_map<EventType, std::unordered_map<std::string, std::function<void(EventBase&)>>> listeners;

    // Event Queues for high-priority and regular events
    std::queue<std::pair<EventType, EventBase&>> highPriorityQueue;
    std::queue<std::pair<EventType, EventBase&>> regularQueue;

    // Synchronization for thread-safe access
    std::mutex mtx;
    std::condition_variable cv;

    // Event processing thread
    std::atomic_bool running;
    std::thread eventThread;
};


#endif // !EVENT_DISPATCHER_HPP
