#include "includes.h"
#include "constants.h"
#include "prototypes.h"

#include "globals.h"

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
