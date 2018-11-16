#include "includes.h"
#include "constants.h"
#include "structs.h"
#include "prototypes.h"
#include "globals.h"

void gamemanager( void ) {
	display();
}

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
