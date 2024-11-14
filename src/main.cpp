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
    dispatcher.addListener(EventType::KeyPress, "PlayerKeyPress", &PlayerController::onKeyPress, &playerController, 1);  // Player ID 1
    dispatcher.addListener(EventType::MouseClick, "UIMouseClick", &UI::onMouseClick, &ui, {"MainScreen"});              // UI view identifier

    // Simulate events
    {
        KeyEvent keyEvent(32);  // e.g., spacebar key code
        dispatcher.dispatch(EventType::KeyPress, keyEvent, "PlayerKeyPress", true);
    }
    MouseEvent mouseEvent(400, 300);  // example coordinates
    dispatcher.dispatch(EventType::MouseClick, mouseEvent, "UIMouseClick");
    dispatcher.dispatch(EventType::MouseClick, mouseEvent, "UIMouseClick");
    dispatcher.dispatch(EventType::MouseClick, mouseEvent, "UIMouseClick");
    dispatcher.dispatch(EventType::MouseClick, mouseEvent, "UIMouseClick");
    dispatcher.dispatch(EventType::MouseClick, mouseEvent, "UIMouseClick");
    dispatcher.dispatch(EventType::MouseClick, mouseEvent, "UIMouseClick");

    std::cout << "Hello!\n";

    {
        KeyEvent keyEvent(11);
        dispatcher.dispatch(EventType::KeyPress, keyEvent, "PlayerKeyPress", true);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Give the event thread some time to process

    return 0;
}