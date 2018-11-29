//#include "scoreboard.h"
#include <GL/glut.h>
#include <stdio.h>

//JUST AN OUTLINE

//clipping window dimensions: clipWindow; bottom lines of octagon and WINDOW_MAX_Y/X
//need NUM MISSILES FIRED; NUM ASTEROIDS ON SCREEN; NUM ASTEROIDS HIT #RATIO OF MIS FIRED TO AST DESTROYED
	//where to get that info from:
		//game.cpp update all these nnumber from there: missiles.size; asteroids.size; resolveCollisions-->points_in_poly



//
void drawString(float x, float y, void *font, const char* string)
{
    //define a character to hold chars of string
    const char *c;
    //position text on screen
    glRasterPos2f(x, y);
    //loop to store current char of string in char defined earlier and add it using glutBitmapCharacter()
    for(c=string; *c!='\0'; c++)
    {
	glutBitmapCharacter(font, *c);
    }
}

void processTextToScreen()
{
    int num = 4;
   
    //define memory to hold string
    char charString[10];
    //put data in string
    sprintf(charString, "Test %d", num);
    glColor3ub(0, 255, 128);
    ////drawString()...
    drawString(150.0, 75.0, GLUT_BITMAP_HELVETICA_12, charString);
    ////clear up string 
}

//put in game render method 
void drawScoreboard()
{
	//process Text to Screen for each portion of scoreboard
	processTextToScreen();//will have a message parameter which stored what will go in sprint
				//and will have messagge variable for each message 
}
