

/// Represents a game, consisting of a map,
///  players, and whatever other data is needed.
/// To be instantiated by the main menu and called inside whatever loop
///  that consists of. Will take RenderWindow for a single render function that
///  will pass it down to all sub objects.

class Game {
public:
    TileSystem map;
    vector<MobileObject> mobs;

};
