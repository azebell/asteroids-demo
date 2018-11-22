#include "game.h"

#include "includes.h"
#include "constants.h"
#include "globals.h"
#include "globals.cpp"
#include "prototypes.h"

// Specify the values to place and size the window on the screen
/* moved to constants.h
const int WINDOW_POSITION_X = 500;
const int WINDOW_POSITION_Y = 5;
const int WINDOW_MAX_X = 1000;
const int WINDOW_MAX_Y = 1000;

const int FRAMERATE = 1000.0/60.0;
*/

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
		case SPACEBAR:
			// missile(ShipTheta); TODO: Get sapceship theta
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'b':
		case 'B':
			g.bustTest();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

//***inputs functs moved to input.cpp / prototypes.h

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

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutSpecialFunc(specialkeys); // key handler for arrow keys
	glutDisplayFunc(gamemanager);
	glutTimerFunc(FRAMERATE,update,0);
	glutMainLoop();
}

