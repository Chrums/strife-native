#include "ISystem.h"
#include "Scene.h"
#include "Component.h"

using namespace Strife::Core;
using namespace std;

vector<Component*> const ISystem::getComponents(std::type_index type) const {
    return scene_->components.get(type);
}
