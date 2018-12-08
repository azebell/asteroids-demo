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
#include "gamekeyboard.h"

// Specify the values to place and size the window on the screen
const int FRAMERATE = 1000.0/60.0;


Game g;
int currTime;
int accumulator; // holds consumable simulation time (ms)

void display( void ) {
	g.render();
}

void update( void ) {
	int nt = glutGet(GLUT_ELAPSED_TIME);
	int ft = nt - currTime; // frame time
	currTime = nt;

	accumulator += ft;
	while(accumulator >= FRAMERATE) {
		g.update();
		accumulator -= FRAMERATE;
	}
	display();
}

// relay functions for key handling
void keyDown(unsigned char key, int x, int y) { g.keyDown(key, x, y); }
void specialKeyDown(int key, int x, int y) { g.specialKeyDown(key, x, y); }
void keyUp(unsigned char key, int x, int y) { g.keyUp(key, x, y); }
void specialKeyUp(int key, int x, int y) { g.specialKeyUp(key, x, y); }


int main(int argc, char** argv) {
	setupGlut(
		Game::WINDOW_POSITION_X,
		Game::WINDOW_POSITION_Y,
		Game::WINDOW_MAX_X,
		Game::WINDOW_MAX_Y
	);

	float radius = 400.0;
	int populace = 50;
	if(argc >= 2)
		radius = atof(argv[1])/2.0;
	if(argc >= 3)
		populace = atoi(argv[2]);

	g.init(Game::WINDOW_MAX_X, Game::WINDOW_MAX_Y, radius, populace);
	currTime = 0;
	accumulator = 0;
        
	glutKeyboardFunc(keyDown);
	glutSpecialFunc(specialKeyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialUpFunc(specialKeyUp);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutDisplayFunc(display);
       	glutIdleFunc(update);
	glutMainLoop();
}

