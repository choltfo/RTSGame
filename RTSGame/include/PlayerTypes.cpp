#include "PlayerTypes.hpp"

bool operator==(const PlayerID & id1, const PlayerID & id2) {
	return id1.id == id2.id;
}

bool operator!=(const PlayerID & id1, const PlayerID & id2) {
	return id1.id != id2.id;
}

std::ostream & operator<<(std::ostream & lhs, const PlayerID & rhs) {
	lhs << "pID {f";
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		lhs << (int)rhs.faction[i];
	}
	return lhs << " p" << rhs.id << "}";
}

PlayerID::PlayerID(){
	id = lPlayer++;

	for (int i = 0; i < MAX_PLAYERS; ++i) {
		faction[i] = Relation::R_ENEMY;
	}

}
