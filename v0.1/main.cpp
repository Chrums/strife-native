#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <fstream>
#include <streambuf>

#include <nlohmann/json.hpp>

#include "Engine.h"
#include "Scene.h"
#include "components/Transform.h"
#include "Delegate.h"
#include "Entity.h"
#include "System.h"

using namespace std;
using nlohmann::json;

class Game : public Engine {

public:
    
    void initialize(Scene* scene) {
        scene->initialize<Transform3f>("transform");
        //scene->initialize<Physics, Body>("body");
    }
    
    void update(void) {
        std::cout << "game update" << std::endl;
    }
    
};

void update(void) {
    std::cout << "update" << std::endl;
}

int main() {
    
    // Scene scene;
    // System<Transform> system(&scene);
    // Entity e0(&scene);
    // Entity e1(&scene);
    // system.add(&e0);
    // system.add(&e1);
    
    Game game;
    Scene* scene = new Scene();
    game.initialize(scene);
    
    try {
        std::ifstream file;
        file.open("/home/environment/strife/project/scenes/default.json");
        json j;
        file >> j;
        scene->deserialize(j);
        cout << "Hello, world!" << endl;
        cout << scene->serialize() << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }
    
    // Delegate<void(void)> updates;
    // updates += update;
    // updates += Bind(&Game::update, game);
    // updates();
    // updates -= update;
    // updates();
    
    return 0;
  
}