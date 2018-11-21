
#include "game.h"
#include <GL/glut.h>

void Game::keyDown(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'b':
		case 'B':
			this->bustTest();
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

