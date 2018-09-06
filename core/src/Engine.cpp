#include "Engine.h"

void Engine::Run(void) {
    scene.Update();
    scene.Render();
};