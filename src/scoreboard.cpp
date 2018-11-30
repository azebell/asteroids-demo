//#include "scoreboard.h"
#include <GL/glut.h>
#include <stdio.h>


void drawString(float x, float y, void *font, const char *text) {
    //define a character to hold chars of string
    const char *c;
    //position text on screen
    glRasterPos2f(x, y);
    //loop to store current char of string in char defined earlier and add it using glutBitmapCharacter()
    for(c=text; *c!='\0'; c++) {
		glutBitmapCharacter(font, *c);
    }
}

void processTextToScreen(float x, float y, float number, const char *textFormat) {
   
    //define memory to hold string
    char charString[20];
    //put data in string
    sprintf(charString, textFormat, number);
    glColor3ub(0, 255, 128);
    ////drawString()...
    drawString(x, y, GLUT_BITMAP_TIMES_ROMAN_24, charString);
    ////clear up string 
}

//TODO
//need to format decimal
//calculate destroyRatio in render method

void drawScoreboard(float number) {
    
    float posFactorX = 1000/6; //change to WINDOW_MAX_X and WINDOW_MAX_Y
    float posFactorY = 1000/10;
    float secondLineFacX = posFactorX+20;
    float thirdLineFacX = posFactorX+40;
    float secondLineFacY = posFactorY-40;
    float thirdLineFacY = posFactorY-60;

    processTextToScreen(posFactorX, posFactorY, 0, "Missiles");
    processTextToScreen(secondLineFacX, secondLineFacY, 0, "Fired");
    processTextToScreen(thirdLineFacX, thirdLineFacY, number, "%d");

    processTextToScreen(posFactorX*2, posFactorY, 0, "Asteroids");
    processTextToScreen(secondLineFacX*2, secondLineFacY, 0, "Visible");
    processTextToScreen(thirdLineFacX*2, thirdLineFacY, number, "%d");

    processTextToScreen(posFactorX*4, posFactorY, 0, "Asteroids");
    processTextToScreen(secondLineFacX*4, secondLineFacY, 0, "Struck");
    processTextToScreen(thirdLineFacX*4, thirdLineFacY, number, "%d");

    processTextToScreen(posFactorX*5, posFactorY, 0, "Destroy");
    processTextToScreen(secondLineFacX*5, secondLineFacY, 0, "Ratio");
    processTextToScreen(thirdLineFacX*5, thirdLineFacY, number, "%d %");

}
