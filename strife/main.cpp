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

class UpdateEvent : public Event {

public:

    UpdateEvent(const Entity& entity) : Event(entity) {}

    static const unsigned int Priority;

    string data;

};

const unsigned int UpdateEvent::Priority = 500;

class RenderEvent : public Event {

public:

    RenderEvent(const Entity& entity) : Event(entity) {}

    static const unsigned int Priority;

    SDL_Renderer* renderer;

};

const unsigned int RenderEvent::Priority = 1000;


void makeTestEvent(TestEvent& event) {
    event.data = "HI!";
}

class TestComponent : public Component {

public:

    static void initialize(System<TestComponent>& system) {
        system.on<TestEvent>(&TestComponent::handleEvent);
        system.on<UpdateEvent>(&TestComponent::update);
        system.on<RenderEvent>(&TestComponent::render);
    }

    static const string Identifier;

    string value;
    int x = 0;

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
        cout << "data:" << e->data << " " << value << " e:" << event->entity.id << endl;
    }

    void update(Event* event) {
        auto e = dynamic_cast<UpdateEvent*>(event);
        //cout << "data:" << e->data << " " << value << endl;
        x += 1;
        Engine::Instance()->dispatcher.trigger<UpdateEvent>(entity);
    }

    void render(Event* event) {
        auto e = dynamic_cast<RenderEvent*>(event);
        //cout << "data:" << e->data << " " << value << endl;
        //x += 1;
        SDL_Rect rect;
        rect.x = x;
        rect.y = 0;
        rect.w = 32;
        rect.h = 32;

        SDL_SetRenderDrawColor(e->renderer, 200, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(e->renderer, &rect);
    }

};

const string TestComponent::Identifier = "Test";

// class Ultima : public Engine {

//     void initialize(Scene scene) {
//         scene.components.initialize<Test>();
//     }

// };


int main() {

    Scene* s = new Scene(Engine::Instance()->dispatcher);
    s->initialize<TestComponent>();

    Entity e0(s);
    TestComponent* t0 = e0.components.add<TestComponent>();
    cout << t0->entity.id << " t0id" << endl;
    t0->value = "0";

    Entity e1(s);
    TestComponent* t1 = e1.components.add<TestComponent>();
    t1->value = "1";

    Engine::Instance()->dispatcher.trigger<TestEvent>(e0, makeTestEvent);
    Engine::Instance()->dispatcher.dispatch(std::type_index(typeid(TestEvent)));
    Engine::Instance()->dispatcher.trigger<TestEvent>(e1, makeTestEvent);
    Engine::Instance()->dispatcher.dispatch();

    json data = s->serialize();
    cout << data << endl;

    Dispatcher dis;
    dis.initialize<TestEvent>();

    auto callback = [=](Event* event, type_index type) {
        //cout << event->data << endl;
    };

    dis.on<TestEvent>(callback);


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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);



    auto makeRenderEvent = [=](RenderEvent& event) {
        event.renderer = renderer;
    };

    Engine::Instance()->dispatcher.trigger<RenderEvent>(e1, makeRenderEvent);
    Engine::Instance()->dispatcher.trigger<UpdateEvent>(e1);
    Engine::Instance()->dispatcher.dispatch();
    SDL_RenderPresent(renderer);

     //Main loop flag
     bool quit = false;
     //Event handler
     SDL_Event e;

     Uint32 startTime = SDL_GetTicks();

     while(!quit) {
       while(SDL_PollEvent(&e) != 0) {
         if (e.type == SDL_QUIT) {
           quit = true;
         }
       }

       Engine::Instance()->dispatcher.trigger<RenderEvent>(e1, makeRenderEvent);
       //Engine::Instance()->dispatcher.trigger<UpdateEvent>(e1);
       Engine::Instance()->dispatcher.dispatch();

       Uint32 runTime = SDL_GetTicks() - startTime;

       if (runTime < 16) {
           Uint32 delayTime = 16 - runTime;
           SDL_Delay(delayTime);
       }
       startTime = SDL_GetTicks();
       SDL_UpdateWindowSurface( window );
     }

    SDL_DestroyWindow(window);
    SDL_Quit();



    delete s;

    return 0;

}
