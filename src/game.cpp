
#include "game.h"
#include "asteroid.h"
#include "spaceship.h"
#include "missile.h"
#include "bust.h"
#include "zgeom.h"
#include "glFuncs.h" // for rendering clipWindow
#include <vector>
#include <cmath>

Game::Game() {

}

void Game::init(int window_width, int window_height, float octRadius) {

	this->origin = { window_width/2.0f, window_height/2.0f };

	// generate some asteroids
	// TODO
	// make placement random
	float x=50.0, y=500.0;
	for(int i=0; i<2; i++) {
		Asteroid a( (vec3) {this->origin.x + x, y} , 25.0 );
		Asteroid b( (vec3) {this->origin.x - x, y} , 25.0 );
		this->asteroids.push_back(a);
		this->asteroids.push_back(b);
		x += 100.0;
	}

	// create the clipping window
	float PI = 3.14159265359;
	float ang = PI/8.0;
	for(int i=0; i<8; i++) {
		this->clipWindow.push_back({
			this->origin.x + (float)cos(ang)*octRadius,
			this->origin.y + (float)sin(ang)*octRadius
		});
		ang += PI/4.0;
	}

    this->spaceship.pos = origin;
}

void Game::update() {
	// update each asteroid
	for(unsigned i=0; i<this->asteroids.size(); i++) {
		this->asteroids[i].update();
	}

	// update each missile
	for(unsigned i=0; i<this->missiles.size(); i++) {
		this->missiles[i].update();
		if( checkClipping(this->missiles[i].Tverts) ) {
			this->missiles.erase(missiles.begin()+i);
			i--;
		}
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
		int clip = this->checkClipping( this->asteroids[i].Tverts );
		if(clip == -1) {
			asteroids[i].pos = 2*origin - asteroids[i].pos;
			asteroids[i].update();
		}
		asteroids[i].clip(this->clipWindow);
		this->asteroids[i].render();
	}

	// Draw the missiles
	for(unsigned i=0; i < this->missiles.size(); i++) {
		this->missiles[i].render();
	}

	// Draw the Spaceship
    this->spaceship.update();
    this->spaceship.render();
	
	swapBuffers();
}

void Game::bustTest() {
	std::vector<Asteroid> bustRoids = bustTris(asteroids[0]);
	this->asteroids.insert(this->asteroids.end(), bustRoids.begin(), bustRoids.end());
	this->asteroids.erase(this->asteroids.begin());
	return;
}

//int Game::checkClipping(Asteroid A) {
int Game::checkClipping(std::vector<vec3> vertices) {
	unsigned outside = 0;
	for(unsigned i=0; i<vertices.size(); i++) {
		if(!point_in_poly(vertices[i], this->clipWindow)) {
			outside += 1;
		}
	}
	if(outside == vertices.size())
		return -1; // completely outside
	return outside; // 0 if fully inside
}

