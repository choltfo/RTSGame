
#pragma once

// A frame's worth of input.
struct UIState {
    bool LMBPressed = false;
    bool RMBPressed = false;
    int8_t scroll = false;

	bool atkMod = false;
	bool stackCommands = false;
	bool SelectMultiple = false;

    sf::FloatRect viewport;
};
