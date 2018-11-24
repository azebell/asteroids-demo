
#ifndef GAME_H
#define GAME_H

#include "asteroid.h"
#include "spaceship.h"
#include "missile.h"
#include "zgeom.h"
#include <vector>

class Game {
private:
public:
	vec3 origin; // will be the center of octagon

	std::vector<Asteroid> asteroids;
	
	std::vector<vec3> clipWindow; // clipping window

    Spaceship spaceship;

	std::vector<Missile> missiles;

	// TODO 
	// add Scoreboard object to game

	Game();
	void init(int window_width, int window_height, float octRadius);
	void update();
	void render();
	int checkClipping(Asteroid A);
	void bustTest();

	// functions to handle keypresses relayed from glut
	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void specialKeyDown(int key, int x, int y);
	void specialKeyUp(int key, int x, int y);
};

#endif // GAME_H

