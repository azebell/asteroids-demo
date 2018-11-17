////////////////////////////////////////
//
// Authors: ____________
// Date: 2018-xx-xx
// Description:
//   Asteroids game.
//
////////////////////////////////////////

#include <GL/glut.h>
#include "zgeom.h"
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

void mouse( int button, int state, int x, int y ) {

	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
	}
	else if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) {
	}
	else if( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN ) {
	}
	glutPostRedisplay();
}


void keyboard( unsigned char key, int x, int y ) {
	switch(key) {
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void specialkeys(int key, int x, int y) {
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
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	setupGlut(
		WINDOW_POSITION_X,
		WINDOW_POSITION_Y,
		WINDOW_MAX_X,
		WINDOW_MAX_Y
	);

	float d = 750.0;
	if(argc >= 2)
		d = atof(argv[1]);

	g.init(WINDOW_MAX_X, WINDOW_MAX_Y, d);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys); // key handler for arrow keys
	glutDisplayFunc(display);
	glutTimerFunc(FRAMERATE,update,0);
	glutMainLoop();
}

