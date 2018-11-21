
#ifndef GAME_H
#define GAME_H

#include "asteroid.h"
#include "spaceship.h"
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
    Spaceship spaceship;

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

	// function to handle keypresses relayed from glut
	void keyHandler(unsigned char key, int x, int y);
	// function to handle special keys (UP, LEFT, RIGHT, DOWN, etc.)
	void specialKeyHandler(int key, int x, int y);
};

#endif // GAME_H

