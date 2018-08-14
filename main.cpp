#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"

int main() {
    
    Scene s;
    
    Entity& e0 = s.AddEntity();
    Entity& e00 = s.AddEntity(e0);
    Entity& e01 = s.AddEntity(e0);
    
    Entity& e1 = s.AddEntity();
    Entity& e10 = s.AddEntity(e1);
    Entity& e11 = s.AddEntity(e1);
    
    s.AddComponentByEntity<Transform>(e0).orientation = 90;
    s.AddComponentByEntity<Transform>(e0).orientation = 180;
    s.AddComponentByEntity<Transform>(e0).orientation = 270;
    
    int counter = 0;
    
    std::vector<std::reference_wrapper<Transform>> e0ts0 = s.GetComponentsByEntity<Transform>(e0);
    for (Transform& transform : e0ts0) {
        transform.position = counter++;
    }
    
    std::vector<std::reference_wrapper<Transform>> e0ts1 = s.GetComponentsByEntity<Transform>(e0);
    for (Transform& transform : e0ts1) {
        std::cout << transform.position << std::endl;
        std::cout << transform.orientation << std::endl;
    }
    
    return 0;
  
}