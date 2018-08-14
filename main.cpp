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
    
    s.AddComponent<Transform>(e0);
    s.AddComponent<Transform>(e0);
    
    //std::vector<std::reference_wrapper<Transform>> e0ts = s.GetComponents<Transform>(e0);
    
    return 0;
  
}