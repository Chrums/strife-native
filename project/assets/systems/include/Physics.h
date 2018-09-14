#ifndef PHYSICS_H
#define PHYSICS_H

#include "Body.h"
#include "Scene.h"
#include "System.h"

class Physics : public System<Body> {

public:
    
    Physics(Scene* scene) :
        System(scene) {};

};

#endif