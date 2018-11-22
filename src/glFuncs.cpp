/*
#include <string.h>	//***moved to includes.h
*/

#include "includes.h"
#include "structs.h"
#include "glFuncs.h"

void setupGlut( int wpx, int wpy, int wdx, int wdy ) {
	// pass dummy args to glutInit
	int myargc = 1;
	char *myargv[1];
	myargv[0] = strdup("empty-arg");
	glutInit(&myargc, myargv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(wdx, wdy);
	glutInitWindowPosition(wpx, wpy);
	glutCreateWindow("Clipping");
	setupGL(wdx, wdy);
}

void setupGL( int wdx, int wdy ) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set viewport to be same dimensions as window
	gluOrtho2D(0.0, wdx, 0.0, wdy);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(2.0);
}

void clearScreen( void ) {
	glClear(GL_COLOR_BUFFER_BIT);
}

void swapBuffers( void ) {
	glutSwapBuffers();
}

