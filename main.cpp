#include <iostream>
#include "Component.h"
#include "Entity.h"
#include "Event.h"
#include "Dispatcher.h"
#include "Scene.h"
#include "Storage.h"
#include "System.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

class FooEvent : public Event {
    
    using Event::Event;
    
public:

    static const Dispatcher::Priority Priority;
        
    int value;
    
    FooEvent(int value)
        : value(value) {}
    
};

const Dispatcher::Priority FooEvent::Priority = Dispatcher::Synchronous;

class BarEvent : public Event {
    
    using Event::Event;
    
public:

    static const Dispatcher::Priority Priority;
        
    int value;
    
    BarEvent(int value)
        : value(value) {}
    
};

const Dispatcher::Priority BarEvent::Priority = 1;

class BazEvent : public Event {
    
    using Event::Event;
    
public:

    static const Dispatcher::Priority Priority;
        
    int value;
    
    BazEvent(int value)
        : value(value) {}
    
};

const Dispatcher::Priority BazEvent::Priority = 2;

class TestComponent : public Component {
    
    using Component::Component;
    
public:

    static void Initialize(System<TestComponent>& system) {
        system.on<FooEvent>(&TestComponent::foo);
        system.on<BarEvent>(&TestComponent::bar);
        system.on<BazEvent>(&TestComponent::baz);
    }
    
    void foo(const FooEvent& f) {
        cout << "foo" << endl;
    }
    
    void bar(const BarEvent& b) {
        cout << "bar" << endl;
    }
    
    void baz(const BazEvent& b) {
        cout << "baz" << endl;
    }
    
};

int main(int argc, char const *argv[]) {
    Scene s;
    s.initialize<TestComponent>();
    s.dispatcher.on<Scene::Entities::AddEvent>(
        [](const Scene::Entities::AddEvent& ae) {
            cout << ae.target.value().id << endl;
        }
    );
    s.dispatcher.on<Scene::Entities::RemoveEvent>(
        [](const Scene::Entities::RemoveEvent& re) {
            cout << re.target.value().id << endl;
        }
    );
    Entity e = s.entities.add();
    e.components.add<TestComponent>();
    s.dispatcher.emit<FooEvent>();
    s.dispatcher.emit<BarEvent>();
    s.dispatcher.emit<BazEvent>();
    s.dispatcher.dispatch();
}