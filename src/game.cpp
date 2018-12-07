#include "gameState.h"
#include "game.h"
#include "asteroid.h"
#include "spaceship.h"
#include "missile.h"
#include "bust.h"
#include "scoreboard.h"
#include "zgeom.h"
#include "gamekeyboard.h"
#include "glFuncs.h" // for rendering clipWindow
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>

Game::Game() {

}

void Game::init(int window_width, int window_height, float octRadius) {

    if(getReset()){
        asteroids.clear();
        clipWindow.clear();
    }
    
    this->octRadius = octRadius;
    this->origin = { window_width/2.0f, window_height/2.0f };

    // generate some asteroids
    // make placement random
    this->tessControl = 0;
    this->spaceship.pos = origin;
    this->spaceship.update();

    srand(time(NULL)); // seed the rand() function with the time

    for(int i=0; i<50; i++) {
        float rando = ((rand()%(int)octRadius)*1.5) - octRadius/1.3; // x position rng
        float rando2 = ((rand()%(int)octRadius)*1.5) - octRadius/1.3; // y position rng
        float arearando = ((rand()%5)) + 5;             // asteroid area rng

        // place dem asteroids randomly son
        Asteroid a( (vec3) {this->origin.x + rando, this->origin.y + rando2} , arearando );
        this->asteroids.push_back(a); // throw em in that vector

        for(int j = 0; j < i; j++){
            // check basteroids for intersections
            // kill em if they do 
            if(poly_intersect(asteroids[j].Tverts, asteroids[i].Tverts) ) {
                this->asteroids.erase(asteroids.begin()+i);
                i--;
            }
        }
        if(poly_intersect(spaceship.Tverts, asteroids[i].Tverts) ) {
        	this->asteroids.erase(asteroids.begin()+i);
        	i--;
        }
    }

    // create the clipping window
    float PI = 3.14159265359;
    float ang = PI/8.0;
    for(int i=0; i<8; i++) {
        this->clipWindow.push_back({
                this->origin.x + (float)cos(ang)*octRadius,
                this->origin.y + (float)sin(ang)*octRadius
                });
        ang += PI/4.0;
    }


    this->missileCount = 0;
    this->destroyRatio = 0.0;
    this->asDestroy = 0;
    this->hitAsteroidType = -1;

    lives = 3;	//give the player 3 lives
    hitTimer = 0;

    this->update();
    setPaused(true);
}

void Game::update() {
	if(getPaused() == false) { //stops updating if user pauses
		if(lives == 0 && !getGameOver()) {
			Asteroid shipToAst = Asteroid(spaceship.pos, spaceship.verts);		//convert ship to burst asteroid

			std::vector<Asteroid> bustRoids = bust(shipToAst);		//bust ship asteroid
			std::vector<Asteroid> bustRoids2 = bust(bustRoids[0]);
			std::vector<Asteroid> bustRoids3 = bust(bustRoids[1]);
			
               		this->asteroids.insert(this->asteroids.begin(), bustRoids2.begin(), bustRoids2.end());
			this->asteroids.insert(this->asteroids.begin(), bustRoids3.begin(), bustRoids3.end());
			setGameOver(true);
		}
	
		if(hitTimer > 0.0){				//handles player hit cooldown
			float currTime = (float)clock();
			hitTimer -= (currTime - startTime) / CLOCKS_PER_SEC;
		}
		else {
			spaceship.hit = false;
		}

		for(unsigned i=0; i<this->missiles.size(); i++) {
			this->missiles[i].update();
			if( checkClipping(this->missiles[i].Tverts) ) {
				this->missiles.erase(missiles.begin()+i);
				i--;
			}
		}

		this->resolveCollisions();

		// update each asteroid
		for(unsigned i=0; i<this->asteroids.size(); i++) {
			this->asteroids[i].update();
			int clip = this->checkClipping( this->asteroids[i].Tverts );
			if(clip == -1) {
				asteroids[i].pos = 2*origin - asteroids[i].pos;
				asteroids[i].update();
			}
			if(clip)
				asteroids[i].clip(this->clipWindow);
		}
		this->resolveOverlaps();

		// update the spaceship
		this->spaceship.update();
	} 
}

void Game::render() {
	clearScreen();

	// draw the clipping window
	glBegin(GL_LINE_LOOP);
	for(unsigned i=0; i < this->clipWindow.size(); i++) {
		glVertex3f(this->clipWindow[i].x, this->clipWindow[i].y, 0.0);
	}
	glEnd();

	// draw the asteroids
	for(unsigned i=0; i < this->asteroids.size(); i++) {
		this->asteroids[i].render(this->tessControl);
	}

	// Draw the missiles
	for(unsigned i=0; i < this->missiles.size(); i++) {
		this->missiles[i].render();
	}


	if(getPaused() == true && getStart() == true) {
		displayText("Press S to Start the Game"); // starting condition message 
	} else if(getPaused() == true && getStart() == false && lives > 0) {
		displayText("Paused: Press P to continue"); // pause message
	} else if(getGameOver() == true && getStart() == false && lives == 0) {
		displayText("Game Over, Press R to Restart");
	}

	// Draw the Spaceship
	if(!getGameOver())
		this->spaceship.render();

	//Draw the Scoreboard

	if(missileCount > 0.0)
		destroyRatio = ((float)asDestroy/(float)missileCount) * 100;
	else
		destroyRatio = 0.0;

	this->scoreboardVals.push_back(missileCount);
	this->scoreboardVals.push_back(this->asteroids.size());
	this->scoreboardVals.push_back(asDestroy);

	score = score + ((hitAsteroidType+1)*50);	//if player hits asteroid update score based on size
	this->scoreboardVals.push_back(score);
	this->hitAsteroidType = -1;

	drawScoreboard(this->scoreboardVals, 1000, 1000, destroyRatio);		//***TODO redefine window size variables with constants from Main.cc
	this->scoreboardVals.clear();

	drawLives(lives, 1000, 1000);

	swapBuffers();
}

//int Game::checkClipping(Asteroid A) {
int Game::checkClipping(std::vector<vec3> vertices) {
    unsigned outside = 0;
    for(unsigned i=0; i<vertices.size(); i++) {
        if(!point_in_poly(vertices[i], this->clipWindow)) {
            outside += 1;
        }
    }
    if(outside == vertices.size())
        return -1; // completely outside
    return outside; // 0 if fully inside
}

void Game::resolveCollisions() {
    for(unsigned k=0; k<this->missiles.size(); k++) {
        for(unsigned i=0; i<this->asteroids.size(); i++) {
            if(poly_intersect(missiles[k].Tverts, this->asteroids[i].Tverts)) {		//missile hits an asteroid

                this->hitAsteroidType = asteroids[i].type;
                std::vector<Asteroid> bustRoids = bust(asteroids[i]);
                this->asteroids.insert(this->asteroids.end(), bustRoids.begin(), bustRoids.end());
                this->asteroids.erase(this->asteroids.begin()+i); 
                asDestroy++;
                this->missiles.erase(missiles.begin()+k);
                k--;
                break;
            }
        }
    }
}

void Game::resolveOverlaps() {
    for(unsigned i=0; i<this->asteroids.size(); i++) {		//check asteorid collisions
        for(unsigned j=0; j<this->asteroids.size(); j++) {	//check collisions with other asteroids
            if(i==j)
                continue;
            if(poly_intersect(asteroids[i].Tverts, asteroids[j].Tverts)) {
                if(asteroids[i].area < asteroids[j].area)
                    asteroids[i].setDrawStyle(Asteroid::FILLED);
                else
                    asteroids[j].setDrawStyle(Asteroid::FILLED);
            }
        }

        if(poly_intersect(asteroids[i].Tverts, spaceship.Tverts)) {	//check collisions with spaceship
            if(lives > 0 && hitTimer <= 0.0) {			
                lives--;		//decrease player lives
                hitTimer = 120.0;	 //active player hit cooldown for num of secs
                startTime = (float)clock();

                spaceship.hit = true;	//change spaceship color to indicate hit
            }
        }
    }
}


