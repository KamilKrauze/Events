#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>

// Event Types
enum class EventType {
    KeyPress,
    MouseClick,
    Custom,
};

// Base Event class - One lvl of polymorphism needed to 
class EventBase {
public:
    EventBase() = default;
    ~EventBase() = default;
};

template<typename DerivedEvent>
class Event : public EventBase
{
public:
    Event() {}
    ~Event() {}

    std::string name() const { DerivedEvent::getName(); }
};

///////////////////////////////////////
///////////   Example events  /////////
///////////////////////////////////////

class KeyEvent : public Event<KeyEvent>
{
private:
    int keyCode;

public:
    KeyEvent(int code) : keyCode(code) {}

    int getKeyCode() const { return keyCode; }
    std::string getName() const { return "KeyEvent"; }
};

class MouseEvent : public Event<MouseEvent>
{
private:
    int x, y;

public:
    MouseEvent(int xPos, int yPos) : x(xPos), y(yPos) {}

    int getX() const { return x; }
    int getY() const { return y; }
    std::string getName() const { return "MouseEvent"; }
};


#endif // ! EVENTS_HPP