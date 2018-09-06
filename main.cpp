#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <exception>

#include "Engine.h"
#include "Scene.h"
#include "Transform.h"
#include "Delegate.h"
#include "Entity.h"

using namespace std;

class Game : public Engine {

public:
    
    void initialize(Scene* scene) {
        scene->initialize<Transform>("transform");
    }
    
    void update(void) {
        std::cout << "game update" << std::endl;
    }
    
};

void update(void) {
    std::cout << "update" << std::endl;
}

int main() {
    
    
    Game game;
    Scene* scene = new Scene();
    game.initialize(scene);
    
    Entity entity(scene);
    std::cout << entity.id << std::endl;
    
    try {
    std::ifstream file;
    file.open("/home/ec2-user/environment/project/assets/scenes/default.json", std::ifstream::in);
    //cout << file.rdbuf() << endl;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(file, pt);
    scene->deserialize(pt);
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