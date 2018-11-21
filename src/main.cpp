////////////////////////////////////////
//
// Authors: ____________
// Date: 2018-xx-xx
// Description:
//   Asteroids game.
//
////////////////////////////////////////

#include <GL/glut.h>
#include "glFuncs.h"
#include "game.h"


// Specify the values to place and size the window on the screen
const int WINDOW_POSITION_X = 500;
const int WINDOW_POSITION_Y = 5;
const int WINDOW_MAX_X = 1000;
const int WINDOW_MAX_Y = 1000;

const int FRAMERATE = 1000.0/60.0;

Game g;

void display( void ) {
	g.render();
}

void update( int value ) {
	glutTimerFunc(FRAMERATE,update,0);
	g.update();
	display();
}


// relay functions for key handling
void keyDown(unsigned char key, int x, int y) { g.keyDown(key, x, y); }
void specialKeyDown(int key, int x, int y) { g.specialKeyDown(key, x, y); }
void keyUp(unsigned char key, int x, int y) { g.keyUp(key, x, y); }
void specialKeyUp(int key, int x, int y) { g.specialKeyUp(key, x, y); }


int main(int argc, char** argv) {

	setupGlut(
		WINDOW_POSITION_X,
		WINDOW_POSITION_Y,
		WINDOW_MAX_X,
		WINDOW_MAX_Y
	);

	float radius = 400.0;
	if(argc >= 2)
		radius = atof(argv[1])/2.0;

	g.init(WINDOW_MAX_X, WINDOW_MAX_Y, radius);

	glutKeyboardFunc(keyDown);
	glutSpecialFunc(specialKeyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialUpFunc(specialKeyUp);

	glutDisplayFunc(display);
	glutTimerFunc(FRAMERATE,update,0);
	glutMainLoop();
}

