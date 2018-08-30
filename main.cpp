#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "Factory.h"
#include "Storage.h"

int main() {
    
    Scene s;
    s.RegisterComponent<Transform>();
    
    Entity& e0 = s.AddEntity();
    Transform& e0t = e0.AddComponent<Transform>();
    e0t.position = 0;
    std::cout << e0t.position << std::endl;
    
    Entity& e1 = s.AddEntity();
    Transform& e1t = e1.AddComponent<Transform>();
    e1t.position = 1;
    std::cout << e1t.position << std::endl;
    
    Entity& e2 = s.AddEntity();
    Transform& e2t = e2.AddComponent<Transform>();
    e2t.position = 2;
    std::cout << e2t.position << std::endl;
    
    Transform& e0t0 = e0.GetComponent<Transform>();
    std::cout << e0t0.position << std::endl;
    
    Transform& e1t0 = e1.GetComponent<Transform>();
    std::cout << e1t0.position << std::endl;
    
    Transform& e2t0 = e2.GetComponent<Transform>();
    std::cout << e2t0.position << std::endl;
    
    // Transform& e0t = transforms.Add(e0.id, e0);
    // e0t.position = 0;
    // Transform& e1t = transforms.Add(e1.id, e1);
    // e1t.position = 1;
    // Transform& e2t = transforms.Add(e2.id, e2);
    // e2t.position = 2;
    
    // transforms.Remove(e2.id);
    // transforms.Remove(e2.id);
    
    // for (auto t : transforms.items_) {
    //     std::cout << t.position << std::endl;
    // }
    
    // Scene s;
    
    // Entity& e0 = s.AddEntity();
    // Entity& e00 = s.AddEntity(e0);
    // Entity& e01 = s.AddEntity(e0);
    
    // Entity& e1 = s.AddEntity();
    // Entity& e10 = s.AddEntity(e1);
    // Entity& e11 = s.AddEntity(e1);
    
    // s.AddComponentByEntity<Transform>(e0).orientation = 90;
    // s.AddComponentByEntity<Transform>(e0).orientation = 180;
    // s.AddComponentByEntity<Transform>(e0).orientation = 270;
    
    // int counter = 0;
    
    // std::vector<std::reference_wrapper<Transform>> e0ts0 = s.GetComponentsByEntity<Transform>(e0);
    // for (Transform& transform : e0ts0) {
    //     transform.position = counter++;
    // }
    
    // std::vector<std::reference_wrapper<Transform>> e0ts1 = s.GetComponentsByEntity<Transform>(e0);
    // for (Transform& transform : e0ts1) {
    //     std::cout << transform.position << std::endl;
    //     std::cout << transform.orientation << std::endl;
    // }
    
    return 0;
  
}