#include "WindowSystem.h"

#include "stdlib.h"

#include <fstream>
#include <iostream>

#include "Event.h"
#include "Scene.h"

using namespace std;
using namespace Strife::Core;

WindowSystem::WindowSystem(Strife::Core::Scene& scene, Dispatcher& dispatcher)
    : ISystem(scene) {
    strcpy(argv_[0], "strife");
    argc_ = 0;
    application_ = new QApplication(argc_, (char**)argv_);

    dispatcher.initialize<RenderEvent>();
    dispatcher.on<RenderEvent>([this](Strife::Core::Event* event, std::type_index type) { pumpQT(event, type); });
}

void WindowSystem::initialize() {}

WindowSystem::~WindowSystem() {
    application_->quit();
    delete application_;
}

void WindowSystem::pumpQT(Strife::Core::Event* event, type_index eventType) {
    application_->processEvents();
}
