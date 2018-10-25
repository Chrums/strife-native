#include "Engine.h"

#include <iostream>
#include <fstream>
#include "Data.h"
#include "Scene.h"

using namespace Strife::Core;
using namespace std;

const unsigned int Engine::TickEvent::Priority = 0;

Engine::TickEvent::TickEvent(const Timer::Time time)
    : time(time) {}

Engine::Scenes::Scenes(Engine& engine)
    : active(nullptr)
    , engine_(engine) {}

void Engine::Scenes::load(const std::string identifier, const std::string path) {
    std::ifstream file;
    file.open(path);
    Data data;
    file >> data;
    auto& [ignore, scene] = *scenes_.try_emplace(identifier).first;
    engine_.initialize(scene);
    scene.deserialize(data);
}

void Engine::Scenes::unload(const std::string identifier) {
    scenes_.erase(identifier);
}

void Engine::Scenes::swap(const std::string identifier) {
    auto& [ignore, scene] = *scenes_.find(identifier);
    active = &scene;
}

Engine* Engine::instance_ = nullptr;

Engine& Engine::Instance() {
	if (Engine::instance_ == nullptr) {
		Engine::instance_ = new Engine();
	}
	return *Engine::instance_;
}

Engine::Engine()
    : scenes(*this) {}

void Engine::initialize(Scene& scene) {}

void Engine::loop() {
    Timer::Time time = timer.update();
    dispatcher.emit<TickEvent>(time);
    loop();
}