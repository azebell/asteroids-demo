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
    	char charString[50];
	sprintf(charString, textToDisplay, 4);
    	glColor3ub(255, 255, 255);
    	drawMessage(400.0, 500.0, GLUT_BITMAP_HELVETICA_18, charString); 
}
