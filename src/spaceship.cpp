#include "spaceship.h"
#include <math.h>
#include <cstdlib>
#include "glFuncs.h"

// creating Spaceship with specified geometry
Spaceship::Spaceship(){
    float wx = 1000, wy = 1000;
    this->verts.push_back( { wx/2, wy/2 });
    this->verts.push_back( { wx/2-10, wy/2+10 });
    this->verts.push_back( { wx/2+20, wy/2 });
    this->verts.push_back( { wx/2-10, wy/2-10 });
    this->Tverts = verts;
}

void Spaceship::setRotationAngle(float angle){
    this->theta = angle;
}

void Spaceship::update() {
    this->theta += this->alpha;

    // TODO
    // update the transform matrix
    // and the Tverts
    this->transform = mat4Identity();
    mat4RotateZ(&this->transform, this->theta);
    mat4Translate(&this->transform, this->pos);
    this->Tverts = applyTransform(this->transform, this->verts);
}


void Spaceship::render() {
    // draw the asteroid
    glBegin(GL_POLYGON);
    for(unsigned i=0; i < this->Tverts.size(); i++) {
        glVertex3f(this->Tverts[i].x, this->Tverts[i].y, 0.0);
    }
    glEnd();
}

