
#include "game.h"
#include <GL/glut.h>

void Game::keyHandler(unsigned char key, int x, int y) {
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

void Game::specialKeyHandler(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			// do something
			break;
		case GLUT_KEY_DOWN:
			// do something
			break;
		case GLUT_KEY_LEFT:
			// do something
			break;
		case GLUT_KEY_RIGHT:
			// do something
			break;
		default:
			break;
	}
}
