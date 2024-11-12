#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include <vector>
#include <unordered_map>

#include "Events.hpp"


class EventDispatcher {
private:
    // Maps each EventType to a list of listeners (callbacks)
    std::unordered_map<EventType, std::vector<std::function<void(EventBase&)>>> listeners;

public:
    // Template method to add a listener function with variadic parameters
    template<typename T, typename EventClass, typename... Args>
    void addListener(EventType type, void (T::* memberFunc)(EventClass&, Args...), T* instance, Args... args) {
        listeners[type].emplace_back([=](EventBase& event) {
            // Downcast EventBase to the specific EventClass type
            if (auto* specificEvent = static_cast<EventClass*>(&event)) {
                // Call the member function with the additional arguments
                (instance->*memberFunc)(*specificEvent, args...);
            }
            });
    }

    // Dispatch an event to the registered listeners for the given type
    void dispatch(EventType type, EventBase& event) {
        if (listeners.find(type) != listeners.end()) {
            for (auto& listener : listeners[type]) {
                listener(event);  // Call each listener with the event
            }
        }
    }
};


#endif // !EVENT_DISPATCHER_HPP
