#include "EventDispatcher.hpp"

EventDispatcher::~EventDispatcher()
{
    running = false;
    cv.notify_all(); // Wake up the thread to exit
    if (eventThread.joinable()) {
        eventThread.join();
    }
}
void EventDispatcher::dispatch(EventType type, EventBase& event, const std::string& listenerKey, bool highPriority)
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (highPriority) {
            highPriorityQueue.push({ type, event });
        }
        else {
            regularQueue.push({ type, event });
        }
    }
    cv.notify_one(); // Notify the event processing thread
}

void EventDispatcher::processEvents()
{
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] {
            return !highPriorityQueue.empty() || !regularQueue.empty() || !running;
            });

        if (!running) break;

        if (!highPriorityQueue.empty()) {
            auto [type, event] = highPriorityQueue.front();
            highPriorityQueue.pop();
            lock.unlock();
            executeListeners(type, event);
        }
        else if (!regularQueue.empty()) {
            auto [type, event] = regularQueue.front();
            regularQueue.pop();
            lock.unlock();
            executeListeners(type, event);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Control processing rate
    }
}

void EventDispatcher::executeListeners(EventType type, EventBase& event)
{
    if (listeners.find(type) != listeners.end()) {
        for (auto& [key, listener] : listeners[type]) {
            listener(event);
        }
    }
}