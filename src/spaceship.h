#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "zgeom.h"
#include <vector>

class Spaceship {
private:
public:
    vec3 pos; // position
    vec3 vel; // velocity
    float theta; // rotation
    float alpha; // rotational velocity
    mat4 transform;
    std::vector<vec3> verts; // polygon vertices
    std::vector<vec3> Tverts; // transformed vertices

    Spaceship();
    void setRotationAngle(float angle);    
    void update();
    void render();
};

#endif // SPACESHIP_H

