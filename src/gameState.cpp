#include "GL/glut.h"
#include "stdio.h"
#include <iostream>
#include <string>

void drawMessage(float x, float y, void *font, const char* string)
{
    	const char *character;
	glRasterPos2f(x, y);
  	for(character = string; *character != '\0'; character++)
	{
		glutBitmapCharacter(font, *character);
	}
}

void displayText(std::string textToDisplay)
{
    int num = 4;
    char charString[50];

    sprintf(charString, textToDisplay.c_str(), num);
    glColor3ub(0, 0, 255);
    drawMessage(500.0, 500.0, GLUT_BITMAP_HELVETICA_12, charString); 
}
