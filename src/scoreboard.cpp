//#include "scoreboard.h"
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
//

using namespace std; 

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
//  put data in string
    sprintf(charString, textFormat, number);
    glColor3ub(0, 255, 128);
//drawString()...
    drawString(x, y, GLUT_BITMAP_TIMES_ROMAN_24, charString);

}                                                                                 


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

void drawLives(int lives, int height, int width){
	float posx = ((float)width/8) * 2;
	float posy = (height/8)*7 + 50;
	int buffer = 50;

	processTextToScreen(posx/2, posy, 0, "Lives : ");

	glColor3ub(255,0,0);		//change color to red
	for(int i = 0; i < lives; i++) {		//draws heart for each life
		glBegin(GL_POLYGON);
			glVertex3f( posx      + (i*buffer) , posy     , 0.0 );		//defines points for a heart
			glVertex3f( posx + 20 + (i*buffer) , posy + 20, 0.0 );
			glVertex3f( posx + 20 + (i*buffer) , posy + 26, 0.0 );
			glVertex3f( posx + 14 + (i*buffer) , posy + 32, 0.0 );
			glVertex3f( posx + 8  + (i*buffer) , posy + 32, 0.0 );
			glVertex3f( posx      + (i*buffer) , posy + 24, 0.0 );
			glVertex3f( posx - 8  + (i*buffer) , posy + 32, 0.0 );
			glVertex3f( posx - 14 + (i*buffer) , posy + 32, 0.0 );
			glVertex3f( posx - 20 + (i*buffer) , posy + 26, 0.0 );
			glVertex3f( posx - 20 + (i*buffer) , posy + 20, 0.0 );
		glEnd();
	}
	glColor3ub(0,255,0);		//change color back to green
}


void updateHighScoreFile()
{
	string filename = "src/HighScores.txt";
        ofstream myfile;
	myfile.open(filename);
	myfile << "hello world" << filename;
	myfile.close(); 
}

void readHighScoreFile()
{
	ifstream infile;
	infile.open("HighScores.txt");

	if(!infile.is_open())		//checks if file is available
	{
		string filename = "src/HighScores.txt";
       		ofstream myfile;
		myfile.open(filename);
		myfile << "hello world" << filename;
		myfile.close(); 
	}
}
