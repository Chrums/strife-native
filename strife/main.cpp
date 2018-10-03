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

#include "components/Transform.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;


class TestEvent : public Event {

public:

    TestEvent(const std::optional<Entity> entity) : Event(entity) {}

    static const unsigned int Priority;

    string data;

};

const unsigned int TestEvent::Priority = 10;

class UpdateEvent : public Event {

public:

    UpdateEvent(const std::optional<Entity> entity) : Event(entity) {}

    static const unsigned int Priority;

    string data;

};

const unsigned int UpdateEvent::Priority = 500;

class RenderEvent : public Event {

public:

    RenderEvent(const std::optional<Entity> entity) : Event(entity) {}

    static const unsigned int Priority;

    SDL_Renderer* renderer;

};

const unsigned int RenderEvent::Priority = 1000;

class BeginRenderEvent : public Event {

public:

    BeginRenderEvent(const std::optional<Entity> entity) : Event(entity) {}

    static const unsigned int Priority;

    SDL_Renderer* renderer;

};

const unsigned int BeginRenderEvent::Priority = 900;

class FinishRenderEvent : public Event {

public:

    FinishRenderEvent(const std::optional<Entity> entity) : Event(entity) {}

    static const unsigned int Priority;

    SDL_Window* window;

};

const unsigned int FinishRenderEvent::Priority = 1100;


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
        json data;
        data["value"] = value;
        data["x"] = x;
        return data;
    };

    void deserialize(json data) {
        value = data["value"];
        x = data["x"];
    };

    void handleEvent(Event* event) {
        auto e = dynamic_cast<TestEvent*>(event);
        cout << "data:" << e->data << " " << entity.id << " " << value << endl;
    }

    void update(Event* event) {
        auto e = dynamic_cast<UpdateEvent*>(event);
        x += 1;

        try {
            auto t = entity.components.get<Transform2f>();
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_RIGHT]) {
                t->translation().x()++;
            }
            if (state[SDL_SCANCODE_LEFT]) {
                t->translation().x()--;
            }
            if (state[SDL_SCANCODE_UP]) {
                t->translation().y()--;
            }
            if (state[SDL_SCANCODE_DOWN]) {
                t->translation().y()++;
            }

        } catch (const std::exception& e) {
            // TODO: Should probably allow for requesting non existent Components w/o exception
        }
    }

    void render(Event* event) {
        auto e = dynamic_cast<RenderEvent*>(event);
        SDL_Rect rect;
        rect.x = x;
        rect.y = 0;
        rect.w = 32;
        rect.h = 32;

        try {
            auto t = entity.components.get<Transform2f>();
            rect.x = t->translation().x();
            rect.y = t->translation().y();
        } catch (const std::exception& e) {
            // TODO: Should probably allow for requesting non existent Components w/o exception
        }

        SDL_SetRenderDrawColor(e->renderer, 200, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(e->renderer, &rect);
    }

};

const string TestComponent::Identifier = "Test";

class RenderSystem : public ISystem {

public:

    RenderSystem(Scene* const scene, Dispatcher& dispatcher) :
        ISystem(scene), dispatcher_(dispatcher) {

        dispatcher_.initialize<BeginRenderEvent>();
        dispatcher_.initialize<FinishRenderEvent>();

        dispatcher_.on<BeginRenderEvent>([this](Event* event, std::type_index type) { beginRender(event, type); });
        dispatcher_.on<FinishRenderEvent>([this](Event* event, std::type_index type) { finishRender(event, type); });
    };

    virtual void initialize() {
    };

    ~RenderSystem() {

    }

    void beginRender(Event* event, std::type_index eventType) {
        BeginRenderEvent* e = dynamic_cast<BeginRenderEvent*>(event);

        SDL_SetRenderDrawColor(e->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(e->renderer);
    }

    void finishRender(Event* event, std::type_index eventType) {
        FinishRenderEvent* e = dynamic_cast<FinishRenderEvent*>(event);

        SDL_UpdateWindowSurface(e->window);
    }



private:

    Dispatcher& dispatcher_;

};

// class Ultima : public Engine {

//     void initialize(Scene scene) {
//         scene.components.initialize<Test>();
//     }

// };


int main() {

    Scene* s = new Scene(Engine::Instance()->dispatcher);
    s->initialize<TestComponent>();
    s->initialize<Transform2f>();
    s->initializeSystem<RenderSystem>();

    Entity e0(s);
    TestComponent* t0 = e0.components.add<TestComponent>();
    Transform2f* tr0 = e0.components.add<Transform2f>();
    cout << t0->entity.id << " t0id " << tr0->translation().x() << endl;
    t0->value = "0";
    t0->x = 0;

    Entity e1(s);
    TestComponent* t1 = e1.components.add<TestComponent>();
    t1->value = "1";
    t1->x = 60;

    // s->deserialize("{\"components\":{\"Test\":{\"60a7adcb-8f76-438c-b95b-150f00507f41\":{\"value\":\"0\",\"x\":0},\"e3140528-624b-4529-991a-423b03ed69a2\":{\"value\":\"1\",\"x\":60}}}}"_json);

    json data = s->serialize();
    cout << data << endl;


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

    auto makeRenderEvent = [=](RenderEvent& event) {
        event.renderer = renderer;
    };
    auto makeBeginRenderEvent = [=](BeginRenderEvent& event) {
        event.renderer = renderer;
    };
    auto makeFinishRenderEvent = [=](FinishRenderEvent& event) {
        event.window = window;
    };

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

       //Engine::Instance()->dispatcher.trigger<TestEvent>(makeTestEvent);
       Engine::Instance()->dispatcher.trigger<UpdateEvent>();
       Engine::Instance()->dispatcher.trigger<RenderEvent>(makeRenderEvent);
       Engine::Instance()->dispatcher.trigger<BeginRenderEvent>(makeBeginRenderEvent);
       Engine::Instance()->dispatcher.trigger<FinishRenderEvent>(makeFinishRenderEvent);
       Engine::Instance()->dispatcher.dispatch();

       Uint32 runTime = SDL_GetTicks() - startTime;

       if (runTime < 16) {
           Uint32 delayTime = 16 - runTime;
           SDL_Delay(delayTime);
       }
       startTime = SDL_GetTicks();
     }

    SDL_DestroyWindow(window);
    SDL_Quit();



    delete s;

    return 0;

}
