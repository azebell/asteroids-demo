
#ifndef GAME_H
#define GAME_H

#include "asteroid.h"
#include "zgeom.h"
#include <vector>

class Game {
private:
public:
	std::vector<Asteroid> asteroids; // base asteroids
	std::vector<Asteroid> triroids; // triangle asteroids
	std::vector<Asteroid> baryroids; // barycentric asteroids
	
	std::vector<vec3> clipWindow; // clipping window

	// TODO 
	// add Ship object to game

	// TODO 
	// add Bullets vector to game

	int missilesFired;
	int hits;
	float accuracy; // hits/missilesFired

	Game();
	void update();
	void render();
};

#endif // GAME_H

