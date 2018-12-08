#include "GL/glut.h"
#include "stdio.h"
#include <iostream>
#include <string>

//Code for drawing a string of characters
void drawMessage(float x, float y, void *font, const char* string)
{
    	const char *character;
	glRasterPos2f(x, y);
  	for(character = string; *character != '\0'; character++)
	{
		glutBitmapCharacter(font, *character);
	}
}

//Displays characters on the screen
void displayText(std::string textToDisplay)
{
	
    	glColor3ub(255, 255, 255);
    	drawMessage(380.0, 550.0, GLUT_BITMAP_HELVETICA_18, textToDisplay.c_str()); 
}
