#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <SDL.h>
#include "Component.h"
#include "Dispatcher.h"
#include "Engine.h"
#include "Entity.h"
#include "Event.h"
#include "Scene.h"
#include "Storage.h"
#include "System.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;


class TestEvent : public Event {

public:

    TestEvent(const Entity& entity) : Event(entity) {}

    static const unsigned int Priority;

    string data;

};

const unsigned int TestEvent::Priority = 10;

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

    void handleEvent(Event* event) {
        auto e = dynamic_cast<TestEvent*>(event);
        cout << "data:" << e->data << endl;
    }

};

const string TestComponent::Identifier = "Test";

// class Ultima : public Engine {

//     void initialize(Scene scene) {
//         scene.components.initialize<Test>();
//     }

// };

void makeTestEvent(TestEvent& event) {
    event.data = "HI!";
}

int main() {

    Scene* s = new Scene();
    s->components.initialize<TestComponent>();

    Entity e0(s);
    TestComponent* const t0 = e0.components.add<TestComponent>();
    t0->value = "0";

    Entity e1(s);
    TestComponent* const t1 = e1.components.add<TestComponent>();
    t1->value = "1";

    Engine::Instance()->dispatcher.initialize<TestEvent>();
    System<TestComponent> sys(s, Engine::Instance()->dispatcher);
    sys.on<TestEvent>(&TestComponent::handleEvent);
    Engine::Instance()->dispatcher.trigger<TestEvent>(e0, makeTestEvent);
    Engine::Instance()->dispatcher.dispatch(std::type_index(typeid(TestEvent)));
    Engine::Instance()->dispatcher.trigger<TestEvent>(e0, makeTestEvent);
    Engine::Instance()->dispatcher.dispatch();

    json data = s->serialize();
    cout << data << endl;

    Dispatcher dis;
    dis.initialize<TestEvent>();

    auto callback = [=](Event* event, type_index type) {
        //cout << event->data << endl;
    };

    dis.on<TestEvent>(callback);

    delete s;


    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
    "SDL2Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    0
    );



    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

     //Main loop flag
     bool quit = false;
     //Event handler
     SDL_Event e;

     while(!quit) {
       while(SDL_PollEvent(&e) != 0) {
         if (e.type == SDL_QUIT) {
           quit = true;
         }
       }
       SDL_UpdateWindowSurface( window );
     }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
