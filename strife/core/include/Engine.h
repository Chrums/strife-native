#ifndef ENGINE_H
#define ENGINE_H

#include "Scene.h"

class Engine {
    
public:
    
    virtual void initialize(Scene* scene) = 0;
    void run();
    
private:

    Scene scene_;
    
};

#endif