////////////////////////////////////////
//
// Author: Avery Zebell
// Date: 2018-xx-xx
// Description:
//   An interactive demonstration of
//   the ear clipping algorithm using
//   OpenGL and GLUT.
//
////////////////////////////////////////

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "zgeom.h"
#include "clipoctagon.h"
#include "glFuncs.h"


// Specify the values to place and size the window on the screen
const int WINDOW_POSITION_X = 500;
const int WINDOW_POSITION_Y = 5;
const int WINDOW_MAX_X = 1000;
const int WINDOW_MAX_Y = 1000;

const int FRAMERATE = 1000.0/60.0;

std::vector<vec3> clipWindow;

void display( void ) {

	clearScreen();

	/* DRAW STUFF */
	glBegin(GL_LINE_LOOP);
	for(unsigned i=0; i<clipWindow.size(); i++) {
		glVertex3f(clipWindow[i].x, clipWindow[i].y, 0.0);
	}
	glEnd();

	swapBuffers();

}

void update( int value ) {
	/* DO STUFF */
	glutTimerFunc(FRAMERATE,update,0);
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

	float d = 400.0;
	if(argc >= 2)
		d = atof(argv[1]);
	clipWindow = genOctagon(WINDOW_MAX_X/2.0, WINDOW_MAX_Y/2.0, d/2.0);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys); // key handler for arrow keys
	glutDisplayFunc(display);
	glutTimerFunc(FRAMERATE,update,0);
	glutMainLoop();
}

