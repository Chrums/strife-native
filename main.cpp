#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <exception>
#include <fstream>
#include <streambuf>

#include <nlohmann/json.hpp>

#include "Body.h"
#include "Engine.h"
#include "Scene.h"
#include "Transform.h"
#include "Delegate.h"
#include "Entity.h"
#include "System.h"
#include "Physics.h"

using namespace std;
using nlohmann::json;

class Game : public Engine {

public:
    
    void initialize(Scene* scene) {
        scene->initialize<Transform>("transform");
        scene->initialize<Physics, Body>("body");
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
        file.open("/home/ec2-user/environment/project/assets/scenes/default.json");
        json j;
        file >> j;
        scene->deserialize(j);
        cout << scene->serialize() << endl;
        // std::stringstream ss;
        // boost::property_tree::write_json(ss, scene->serialize());
        // boost::property_tree::ptree pt2;
        // boost::property_tree::read_json(ss, pt2);
        // boost::property_tree::write_json(ss, scene->serialize());
        // cout << ss.str() << endl;
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