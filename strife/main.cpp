#include <iostream>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <SDL.h>
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
