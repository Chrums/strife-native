#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include "ISystem.h"
#include "Dispatcher.h"
#include "events/OnGui.h"
#include "events/SelectEntity.h"
#include <SDL.h>
#include <typeindex>
#include "Entity.h"
#include <unordered_set>

class Scene;

class ComponentList : public Strife::Core::ISystem {
public:
	ComponentList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

	~ComponentList();

	void render(const OnGui& event);

private:
	bool active_;
	std::unordered_set<Strife::Core::Entity> currentEntities_;

	std::type_index addComponentType_;

	void selectEntity(const SelectEntity& event);
};

#endif
