#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include "Scene.h"
#include "Entity.h"

using namespace Strife;
using namespace std;

int main() {
    
    Scene* s = new Scene();
    Entity* e0 = new Entity(s);
    // Entity* e00 = new Entity(s);
    // e00->setParent(e0);
    // Entity* e01 = new Entity(s);
    // e01->setParent(e0);
    // Entity* e1 = new Entity(s);
    
    // cout << e0->id << endl;
    // for (auto child : e0->getChildren()) {
    //     cout << child->id << endl;
    // }
    
    return 0;
  
}