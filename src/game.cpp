
#include "game.h"
#include "asteroid.h"
#include "zgeom.h"
#include "glFuncs.h" // for rendering clipWindow
#include <vector>
#include <cmath>

Game::Game() {

}

void Game::init(int window_width, int window_height, float octDiameter) {

	// generate some asteroids
	// TODO
	// make placement random
	float x=100.0, y=500.0;
	for(int i=0; i<10; i++) {
		Asteroid a( (vec3) {x, y} );
		this->asteroids.push_back(a);
		x += 100.0;
	}

	// create the clipping window
	float PI = 3.14159265359;
	float cx = window_width/2.0, cy = window_height/2.0;
	float radius = octDiameter/2.0;
	float step = PI/4.0;
	float ang = PI/8.0;
	for(int i=0; i<8; i++) {
		this->clipWindow.push_back({
			cx + (float)cos(ang)*radius,
			cy + (float)sin(ang)*radius
		});
		ang += step;
	}
}

void Game::update() {
	// update each asteroid
	for(unsigned i=0; i<this->asteroids.size(); i++) {
		this->asteroids[i].update();
	}
}

void Game::render() {

	clearScreen();

	// draw the clipping window
	glBegin(GL_LINE_LOOP);
	for(unsigned i=0; i < this->clipWindow.size(); i++) {
		glVertex3f(this->clipWindow[i].x, this->clipWindow[i].y, 0.0);
	}
	glEnd();

	// draw the asteroids
	for(unsigned i=0; i < this->asteroids.size(); i++) {
		this->asteroids[i].render();
	}
	
	swapBuffers();
}

