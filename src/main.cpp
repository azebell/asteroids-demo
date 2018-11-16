/*
#include <GL/glut.h>		//***moved to includes.h
#include <stdio.h>
#include <vector>
#include "zgeom.h"
#include "clipoctagon.h"
#include "glFuncs.h"
*/

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

//std::vector<vec3> clipWindow;		//***moved to globals.h

//***display/update functs moved to gamemanager.cpp

//***inputs functs moved to input.cpp / prototypes.h

int main(int argc, char** argv) {

	setupGlut(
		WINDOW_POSITION_X,
		WINDOW_POSITION_Y,
		WINDOW_MAX_X,
		WINDOW_MAX_Y
	);

	float octrad = WINDOW_MAX_X/2;
	float octbuffer = 15;
	if(argc >= 2)
		octrad = atof(argv[1]);
	clipWindow = genOctagon(WINDOW_MAX_X/2.0, WINDOW_MAX_Y/2.0, octrad - octbuffer);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys); // key handler for arrow keys
	glutDisplayFunc(gamemanager);
	glutTimerFunc(FRAMERATE,update,0);
	glutMainLoop();
}

