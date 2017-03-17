#pragma once

#include <inttypes.h>

#define MAX_PLAYERS 16

enum Relation {
	R_IS = 0,
	R_FRIENDLY = 1,
	R_ENEMY = 2,
	R_NEUTRAL = 4,
};

struct PlayerID {
	int id;
	Relation faction[MAX_PLAYERS];
};