#define _POSIX_SOURCE
#include "gameState.h"
#include "game.h"
#include <GL/glut.h>
#include "unistd.h"
#include <sys/types.h> 
#include <signal.h> 
static bool paused = false;

void Game::keyDown(unsigned char key, int x, int y) {
	switch(key) {
		case 's':
		case 'S':
			break;
		case 'p':
		case 'P':
			
			pause();
			break;

		case 't':
		case 'T':
			break;
		
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 32: // Spacebar
			missiles.push_back(
				Missile(this->spaceship.pos, this->spaceship.theta)
			);
			break;
		default:
			break;
	}
}

void Game::keyUp(unsigned char key, int x, int y) {
	// handle key release
}

void Game::specialKeyDown(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
            //do nothing
            break;
		case GLUT_KEY_DOWN:
			// do nothing
			break;
		case GLUT_KEY_LEFT:
			spaceship.alpha = 0.1;
			break;
		case GLUT_KEY_RIGHT:
			spaceship.alpha = -0.1;
			break;
		default:
			break;
	}
}

void Game::specialKeyUp(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			spaceship.alpha = 0.0;
			break;
		case GLUT_KEY_RIGHT:
			spaceship.alpha = 0.0;
			break;
		default:
			break;
	}
}

bool getPaused() {
	return paused;
}
