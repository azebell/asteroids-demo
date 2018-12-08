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
    const static int WINDOW_POSITION_X = 500;
    const static int WINDOW_POSITION_Y = 5;
    const static int WINDOW_MAX_X = 1000;
    const static int WINDOW_MAX_Y = 1000;

	vec3 origin; // will be the center of octagon
	std::vector<vec3> clipWindow; // clipping window

	std::vector<Asteroid> asteroids;
	int tessControl;
	Spaceship spaceship;
	std::vector<Missile> missiles;

	std::vector<int> scoreboardVals;
        int missileCount;
	int asDestroy;
	float destroyRatio;
	float octRadius;
    int hitAsteroidType;
	int score;

	int lives;
	float startTime;
	float hitTimer;

	Game();
	void init(int window_width, int window_height, float octRadius);
	void update();
	void render();
	int checkClipping(std::vector<vec3> vertices);
	void resolveCollisions();
	void resolveOverlaps();

	// functions to handle keypresses relayed from glut
	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void specialKeyDown(int key, int x, int y);
	void specialKeyUp(int key, int x, int y);
};

#endif // GAME_H

