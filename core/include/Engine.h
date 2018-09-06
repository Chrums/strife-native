#ifndef ENGINE_H
#define ENGINE_H

#include "Scene.h"

class Engine {
    
public:
    
    virtual void Register(Scene* scene) = 0;
    void Run(void);
    
private:

    Scene scene;
    
};

#endif