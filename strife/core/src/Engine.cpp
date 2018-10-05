#include "Engine.h"

using namespace Strife::Core;
using namespace std;

Engine::Scenes::Scenes(Engine& engine) :
    engine_(engine) {};

Engine* Engine::instance_ = nullptr;

Engine* Engine::Instance() {
    if (Engine::instance_ == nullptr) {
        Engine::instance_ = new Engine();
    }
    return Engine::instance_;
}

Engine::Engine() :
    scenes(*this) {};
    
void Engine::initialize() {};