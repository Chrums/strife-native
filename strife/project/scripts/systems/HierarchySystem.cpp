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

const std::unordered_set<Strife::Core::Entity>& HierarchySystem::getChildren(std::optional<Strife::Core::Entity> root) {
	return children_[root];
}

void HierarchySystem::parentChanged(const ParentChanged &event) {
	if (children_.find(event.previousParent) != children_.end()) {
		children_[event.previousParent].erase(event.changedEntity);
	}
	children_[event.newParent].insert(event.changedEntity);
}
