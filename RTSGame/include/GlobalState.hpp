
#pragma once

// A frame's worth of input.
struct GlobalState {
    bool LMBPressed = false;
    bool RMBPressed = false;
    int8_t scroll = false;

    sf::FloatRect viewport;
};
