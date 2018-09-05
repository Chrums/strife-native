#include <iostream>
#include <boost/uuid/uuid_io.hpp>

#include "Engine.h"
#include "Scene.h"
#include "Transform.h"

class Game : public Engine {

public:
    
    void Register(Scene* scene) {
        scene->Register<Transform>();
    }
    
};

int main() {
    
    Game game;
    
    return 0;
  
}