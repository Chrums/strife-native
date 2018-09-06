#include "Engine.h"

void Engine::run() {
    scene_.update();
    scene_.render();
};