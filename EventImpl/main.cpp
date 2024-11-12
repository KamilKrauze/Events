#include "Events.hpp"
#include "EventDispatcher.hpp"
#include "Components.hpp"

#include <string>

int main() {
    // Create dispatcher and components
    EventDispatcher dispatcher;
    //EventDispatcher dispatcher2;
    PlayerController playerController;
    UI ui;

    // Register event listeners with additional parameters
    dispatcher.addListener(EventType::KeyPress, &PlayerController::onKeyPress, &playerController, 1);  // Player ID 1
    dispatcher.addListener(EventType::MouseClick, &UI::onMouseClick, &ui, { "hello" });              // UI view identifier

    // Simulate events
    KeyEvent keyEvent(32);  // e.g., spacebar key code
    dispatcher.dispatch(EventType::KeyPress, keyEvent);

    MouseEvent mouseEvent(400, 300);  // example coordinates
    dispatcher.dispatch(EventType::MouseClick, mouseEvent);

    std::cout << COUNT_VARARGS() << "\n";

    return 0;
}

