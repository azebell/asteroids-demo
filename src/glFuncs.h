#ifndef GLFUNCS_H
#define GLFUNCS_H

//#include <GL/glut.h>		//***moved to includeds.h

#include "includes.h"
#include "structs.h"

void setupGlut( int wpx, int wpy, int wdx, int wdy );

void setupGL( int wdx, int wdy );

void clearScreen( void );

void swapBuffers( void );

#endif // GLFUNCS_H

