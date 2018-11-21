#include "spaceship.h"
#include <math.h>
#include <cstdlib>
#include "glFuncs.h"
#include <iostream>

// creating Spaceship with specified geometry
Spaceship::Spaceship(){
    float wx = 1000, wy = 1000;
    this->vel = {0.0,0.0,0.0};
    this->verts.push_back( { wx/2, wy/2 });
    this->verts.push_back( { wx/2-10, wy/2+10 });
    this->verts.push_back( { wx/2+20, wy/2 });
    this->verts.push_back( { wx/2-10, wy/2-10 });
    this->Tverts = verts;
}

void Spaceship::setRotationAngle(float angle){
    std::cout << "theta: " << theta << " angle: "<< angle << std::endl; 
    if(alpha == 0)
        this -> alpha = angle;
    else{
        alpha = 0;
        angle = 0;
    }
}

// update Spaceship with new rotation direction
void Spaceship::update() {
    
    this->theta += this->alpha;

    // not rotating around origin
    this->transform = mat4Identity();
    mat4RotateZ(&this->transform, this->theta); 
    this->Tverts = applyTransform(this->transform, this->verts);
    this -> alpha = 0;
}


void Spaceship::render() {
    // draw the asteroid
    glBegin(GL_POLYGON);
    for(unsigned i=0; i < this->Tverts.size(); i++) {
        glVertex3f(this->Tverts[i].x, this->Tverts[i].y, 0.0);
    }
    glEnd();
}

