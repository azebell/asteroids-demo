
#ifndef GAME_H
#define GAME_H

#include "asteroid.h"
#include "zgeom.h"
#include <vector>

class Game {
private:
public:
	vec3 origin; // will be the center of octagon

	std::vector<Asteroid> asteroids;
	
	std::vector<vec3> clipWindow; // clipping window

	// TODO 
	// add Ship object to game

	// TODO 
	// add Bullets vector to game

	// TODO 
	// add Scoreboard object to game

	Game();
	void init(int window_width, int window_height, float octRadius);
	void update();
	void render();
	int checkClipping(Asteroid A);
	void bustTest();
};

#endif // GAME_H

