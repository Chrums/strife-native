#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include "Component.h"
#include "Entity.h"
#include "Scene.h"
#include "Storage.h"

using namespace Strife;
using namespace std;

class Test : public Component {

public:

    Test(const Entity* const entity) :
        Component(entity) {};
        
    Test(boost::uuids::uuid id, const Entity* const entity) :
        Component(id, entity) {};
    
};

int main() {
    
    Scene* s = new Scene();
    s->components.initialize<Test>("Test");
    
    const Entity* const e0 = s->entities.add();
    Test* const t0 = e0->components.add<Test>();
    
    const Entity* const e1 = s->entities.add();
    Test* const t1 = e1->components.add<Test>();
    
    //Scene* s = new Scene();
    //s->components.initialize<Test>("test");
    
    //const Entity* const e0 = s->entities.add();
    
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