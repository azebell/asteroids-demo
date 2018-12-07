//#include "scoreboard.h"
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <iostream>
//
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
//std::cout << "Start process text" << std::endl;
//define memory to hold string
    char charString[20];
//  put data in string
    sprintf(charString, textFormat, number);
    glColor3ub(0, 255, 128);
//drawString()...
    drawString(x, y, GLUT_BITMAP_TIMES_ROMAN_24, charString);

}                                                                                  //TODO


void drawScoreboard(std::vector<int> values, int height, int width, float ratio) {

float numMis = (float) values[0];
float numAs = (float) values[1];
float numDestroy = (float) values[2];
float posFactorX = ((float)width/8);
float posFactorY =(float) (height/8)*0.75;
float totscore = (float)values[3];

processTextToScreen(posFactorX, posFactorY, numMis, "Missiles Fired : %.0f");                               
processTextToScreen(posFactorX, posFactorY-40, numAs, "Asteroids Visible : %.0f");

processTextToScreen(posFactorX*5.50, posFactorY, ratio, "Destroy Ratio : %.2f %");

processTextToScreen(posFactorX*5.50, posFactorY-40, numDestroy, "Asteroids Struck : %.0f");

processTextToScreen(posFactorX*5.50, posFactorY-80, totscore, "Total Score : %.0f");

}
