#include "HierarchySystem.h"

#include "Scene.h"
#include "Dispatcher.h"
#include "events/ParentChanged.h"

HierarchySystem::HierarchySystem(Strife::Core::Scene &scene, Strife::Core::Dispatcher &dispatcher)
    : ISystem(scene)
    , dispatcher_(dispatcher) {

	dispatcher.on<ParentChanged>([this](const ParentChanged& event) { parentChanged(event); });
}

HierarchySystem::~HierarchySystem() {}

void HierarchySystem::parentChanged(const ParentChanged &event) {
	if (children_.find(event.previousParent) != children_.end()) {
		children_[event.previousParent].erase(event.changedEntity);
	}
	if (event.newParent.has_value() && children_.find(event.newParent.value()) != children_.end()) {
		children_[event.newParent].insert(event.changedEntity);
	}
}
