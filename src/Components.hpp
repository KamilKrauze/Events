#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include <string_view>

#include "Events.hpp"

class PlayerController {
public:
    // Event listener with additional parameters (like player id)
    void onKeyPress(KeyEvent& event, int playerId) {
        std::cout << "Player " << playerId << ": Key pressed with code " << event.getKeyCode() << "\n";
    }
};

class UI {
public:
    // Event listener with additional parameters (like screen position)
    void onMouseClick(MouseEvent& event, std::string_view view) {
        std::cout << "UI [" << view << "]: Mouse clicked at (" << event.getX() << ", " << event.getY() << ")\n";
    }
};



#endif // !PLAYER_CONTROLLER_HPP
