#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Entity.h"
#include "Scene.h"
#include "Storage.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

class Test : public Component {
    
public:

    string value;
    
    Test(const Entity& entity) :
        Component(entity) {};
        
    Test(const uuid id, const Entity& entity) :
        Component(id, entity) {};
        
    const json serialize() const {
        return value;
    };
    
    void deserialize(json data) {
        value = data.get<string>();
    };
    
};

int main() {
    
    Scene* s = new Scene();
    s->components.initialize<Test>("test");
    
    Entity e0(s);
    Test* const t0 = e0.components.add<Test>();
    t0->value = "0";
    
    Entity e1(s);
    Test* const t1 = e1.components.add<Test>();
    t1->value = "1";
    
    json data = s->serialize();
    cout << data << endl;
    
    Scene* d = new Scene();
    d->components.initialize<Test>("test");
    
    d->deserialize(data);
    cout << d->serialize() << endl;
    
    delete s;
    delete d;
    
    return 0;
  
}