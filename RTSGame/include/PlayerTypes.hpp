#pragma once

#include <inttypes.h>
#include <iostream>

#define MAX_PLAYERS 16

enum Relation {
	R_IS = 0,
	R_FRIENDLY = 1,
	R_ENEMY = 2,
	R_NEUTRAL = 4,
};

static int lPlayer;

struct PlayerID {
	

	int id;
	Relation faction[MAX_PLAYERS];

	PlayerID();

	friend bool operator== (const PlayerID &id1, const PlayerID &id2);
	friend bool operator!= (const PlayerID &id1, const PlayerID &id2);


	friend std::ostream& operator<<(std::ostream& lhs, const PlayerID& rhs);
};