#ifndef HIERARCHYSYSTEM_H
#define HIERARCHYSYSTEM_H

#include "ISystem.h"
#include "Dispatcher.h"
#include "unordered_map"
#include "Entity.h"
#include "events/ParentChanged.h"

#include <unordered_map>
#include <unordered_set>

class Scene;

class HierarchySystem : public Strife::Core::ISystem {
public:
	HierarchySystem(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

	~HierarchySystem();

private:
	Strife::Core::Dispatcher& dispatcher_;

	std::unordered_map<std::optional<Strife::Core::Entity>, std::unordered_set<Strife::Core::Entity>> children_;

	void parentChanged(const ParentChanged& event);
};

#endif
