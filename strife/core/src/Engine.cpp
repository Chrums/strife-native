#include "Engine.h"

#include <fstream>
#include "Data.h"
#include "Scene.h"

using namespace Strife::Core;
using namespace std;

Engine::Scenes::Scenes(Engine& engine)
    : active(nullptr)
    , engine_(engine) {}

void Engine::Scenes::load(const std::string identifier, const std::string path) {
    std::ifstream file;
    file.open(path);
    Data data;
    file >> data;
    this->try_emplace(identifier, engine_.dispatcher);
}

void Engine::Scenes::unload(const std::string identifier) {
    this->erase(identifier);
}

void Engine::Scenes::swap(const std::string identifier) {
    auto& [ignore, scene] = *this->find(identifier);
    active = &scene;
}

Engine* Engine::instance_ = nullptr;

Engine* Engine::Instance() {
	if (Engine::instance_ == nullptr) {
		Engine::instance_ = new Engine();
	}
	return Engine::instance_;
}

Engine::Engine()
    : scenes(*this) {}

void Engine::initialize(Scene& scene) {}
