<<<<<<< HEAD
=======
#include "gameState.h"
>>>>>>> origin/th
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

Game::Game() {

}

void Game::init(int window_width, int window_height, float octRadius) {

    this->origin = { window_width/2.0f, window_height/2.0f };

    // generate some asteroids
    // make placement random 
    
    srand(time(NULL)); // seed the rand() function with the time
    
    for(int i=0; i<50; i++) {
        float rando = ((rand()%(int)octRadius)*2) - octRadius; // x position rng
        float rando2 = ((rand()%(int)octRadius)*2) - octRadius; // y position rng
        float arearando = ((rand()%5)) + 5;             // asteroid area rng

        // place dem asteroids randomly son
        Asteroid a( (vec3) {this->origin.x + rando, this->origin.y + rando2} , arearando );
        this->asteroids.push_back(a); // throw em in that vector


        for(int j = 0; j < i; j++){
            // check basteroids for intersections
            // kill em if they do 
            if(poly_intersect(asteroids[j].Tverts, asteroids[i].Tverts)) {
                this->asteroids.erase(asteroids.begin()+i);
                i--;
            }
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


    this->spaceship.pos = origin;
}

void Game::update() {
<<<<<<< HEAD
    // update each missile
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
        asteroids[i].clip(this->clipWindow);
    }

    this->resolveOverlaps();
    // update the spaceship
    this->spaceship.update();

    //update scoreboard values here
}

void Game::render() {

    clearScreen();

    glColor3ub(255,255,255);
=======
	
	if(getPaused() == false) { //stops updating if user pauses
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
			asteroids[i].clip(this->clipWindow);
		}

		// update the spaceship
    		this->spaceship.update();
	} 
}

void Game::render() {
	clearScreen();
>>>>>>> origin/th

    // draw the clipping window
    glBegin(GL_LINE_LOOP);
    for(unsigned i=0; i < this->clipWindow.size(); i++) {
        glVertex3f(this->clipWindow[i].x, this->clipWindow[i].y, 0.0);
    }
    glEnd();

    // draw the asteroids
    for(unsigned i=0; i < this->asteroids.size(); i++) {
        this->asteroids[i].render();
    }

<<<<<<< HEAD
    // Draw the missiles
    for(unsigned i=0; i < this->missiles.size(); i++) {
        this->missiles[i].render();
    }
=======
	// Draw the missiles
	for(unsigned i=0; i < this->missiles.size(); i++) {
		this->missiles[i].render();
	}
	
	if(getPaused() == true && getStart() == true) {
                displayText("Press s to start the game"); // starting condition message 
        } else if(getPaused() == true && getStart() == false) {
                displayText("Paused: Press p to continue"); // pause message
        }

>>>>>>> origin/th

    // Draw the Spaceship
    this->spaceship.render();
<<<<<<< HEAD

    //Draw Scoreboard
    //TODO
    //make a vector size 4 to update each time with the correct numbers 
    //and pass that instead to the function. That way you can just take the 
    //values from that and assign them properly
    drawScoreboard(10.0);

    swapBuffers();
=======
	swapBuffers();
>>>>>>> origin/th
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
            if(point_in_poly(missiles[k].Tverts[1], this->asteroids[i].Tverts)) {
                std::vector<Asteroid> bustRoids = bust(asteroids[i]);
                this->asteroids.insert(this->asteroids.end(), bustRoids.begin(), bustRoids.end());
                this->asteroids.erase(this->asteroids.begin()+i);
                this->missiles.erase(missiles.begin()+k);
                k--;
                break;
            }
        }
    }
}

void Game::resolveOverlaps() {
    for(unsigned i=0; i<this->asteroids.size(); i++) {
        for(unsigned j=0; j<this->asteroids.size(); j++) {
            if(i==j)
                continue;
            if(poly_intersect(asteroids[i].Tverts, asteroids[j].Tverts)) {
                float A1 = area_of_tris(asteroids[i].verts);
                float A2 = area_of_tris(asteroids[j].verts);
                if(A1 < A2)
                    asteroids[i].setDrawStyle(Asteroid::FILLED);
                else
                    asteroids[j].setDrawStyle(Asteroid::FILLED);
            }
        }
    }
}

