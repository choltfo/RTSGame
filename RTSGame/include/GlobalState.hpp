
#pragma once

// A frame's worth of input.
struct GlobalState {
    bool LMBPressed = false;
    bool RMBPressed = false;
    int8_t scroll = false;

	bool atkMod = false;
	bool stackCommands = false;

    sf::FloatRect viewport;
};
