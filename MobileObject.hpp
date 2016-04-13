
#include <SFML/System.hpp>

enum Direction {
    DOWN,
    DOWNRIGHT,
    RIGHT,
    UPRIGHT,
    UP,
    UPLEFT,
    LEFT,
    DOWNLEFT
};

// This is a bad design. Sprites are not designed to work in reams.
// That said, there will only be one per unit. Perhaps it wouldn't be too bad?
// It would only use a couple hundred kilobytes of VRAM storing all the textures (assuming 32x32px, 8 frames, and 15 animations),
//  but the draw calls would be all over the place.
class MOBTemplate {
public:
    sf::texture * staticTextures[8];
    std::vector<sf::texture> walkLoops[8];
};

class MobileObject {
public:
    sf::Vector2f position;
    Direction direction;
    uint8_t render(sf::RenderWindow window)
    MOBTemplate * type;
};


