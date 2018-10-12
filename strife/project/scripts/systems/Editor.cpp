#include "Editor.h"
#include "Scene.h"
#include "forms/MainWindow.h"

using namespace std;

Editor::Editor(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher)
    : Strife::Core::ISystem(scene) {
    entityList_.show();
}

void Editor::initialize() {}

Editor::~Editor() {}
