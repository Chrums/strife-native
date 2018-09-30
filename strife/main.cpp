#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Dispatcher.h"
#include "Engine.h"
#include "Entity.h"
#include "Event.h"
#include "Scene.h"
#include "Storage.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

class TestEvent : public Event {
    
public:

    static const unsigned int Priority;
    
    string data;
    
};

const unsigned int TestEvent::Priority = Event::Synchronous;

class TestComponent : public Component {
    
public:

    static const string Identifier;

    string value;
    
    TestComponent(const Entity& entity) :
        Component(entity) {};
        
    TestComponent(const uuid id, const Entity& entity) :
        Component(id, entity) {};
        
    const json serialize() const {
        return value;
    };
    
    void deserialize(json data) {
        value = data.get<string>();
    };
    
};

const string TestComponent::Identifier = "Test";

// class Ultima : public Engine {
    
//     void initialize(Scene scene) {
//         scene.components.initialize<Test>();
//     }
    
// };



int main() {
    
    Scene* s = new Scene();
    s->components.initialize<TestComponent>();
    
    Entity e0(s);
    TestComponent* const t0 = e0.components.add<TestComponent>();
    t0->value = "0";
    
    Entity e1(s);
    TestComponent* const t1 = e1.components.add<TestComponent>();
    t1->value = "1";
    
    json data = s->serialize();
    cout << data << endl;
    
    Dispatcher d;
    d.initialize<TestEvent>();
    
    auto callback = [=](Event* event) {
        //cout << event->data << endl;
    };
    
    d.on<TestEvent>(callback);
    
    delete s;
    
    return 0;
  
}