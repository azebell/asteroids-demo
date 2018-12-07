#include "gameState.h"
#include "game.h"
#include <GL/glut.h>
#include <sys/types.h> 
#include <signal.h> 
#include <iostream>

static bool paused = false;
static bool start = true;
static bool gameover = false;
static bool reset = false;

void Game::keyDown(unsigned char key, int x, int y) {
	switch(key) {
		case 's':
		case 'S':
			if(start == true) {
				paused = !paused;
				start = !start;
			}
			break;
		case 'p':
		case 'P':		
			paused = !paused;
			if(paused) {
				displayText("Paused, Press P to continue playing");	
			}
			break;
        case 'r':
        case 'R':
            if(reset == false){
                reset = true;
		gameover = false;
                init(1000,1000,400);
                update();
                render();
                reset = false;
            }
            break;
		case 't':
		case 'T':
			if(this->tessControl == 0){
				this->tessControl = 1;				
			}
			else{
				this->tessControl = 0;
			}
			break;
		
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 32: // Spacebar
			missiles.push_back(
				Missile(this->spaceship.pos, this->spaceship.theta)
			); 
			missileCount++;
			break;
		default:
			break;
	}
}

void Game::keyUp(unsigned char key, int x, int y) {
	// handle key release
}

void Game::specialKeyDown(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
            //do nothing
            break;
		case GLUT_KEY_DOWN:
			// do nothing
			break;
		case GLUT_KEY_LEFT:
			spaceship.alpha = 0.1;
			break;
		case GLUT_KEY_RIGHT:
			spaceship.alpha = -0.1;
			break;
		default:
			break;
	}
}

void Game::specialKeyUp(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			spaceship.alpha = 0.0;
			break;
		case GLUT_KEY_RIGHT:
			spaceship.alpha = 0.0;
			break;
		default:
			break;
	}
}
// Returns if the game is paused
bool getPaused() {
	return paused;
}
// Returns if the game is in the starting state
bool getStart() {
	return start;
}

bool getReset(){
	return reset;
} 

bool getGameOver(){
	return gameover;
}

// Sets the pause state flag
void setPaused(int value){
	paused = value;
}

// Sets the start state flag
void setStart(int value){
	start = value;
}

// Sets the reset state flag
void setReset(int value){
	reset = value;
}

void setGameOver(int value){
	gameover = value;
}

