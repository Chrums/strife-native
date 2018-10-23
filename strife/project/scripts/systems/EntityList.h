#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "ISystem.h"
#include "Dispatcher.h"
#include "events/OnGui.h"
#include "Entity.h"
#include <typeindex>
#include <unordered_set>

class Scene;

class EntityList : public Strife::Core::ISystem {
public:
	EntityList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

	~EntityList();

	void render(const OnGui& event);

private:
	bool active_;

	std::unordered_set<Strife::Core::Entity> selectedEntities_;

	std::type_index addComponentType_;

	Strife::Core::Dispatcher& dispatcher_;

	std::optional<Strife::Core::Entity> renderEntity(std::optional<Strife::Core::Entity> entity);
	bool renderEntityContextMenu(std::optional<Strife::Core::Entity> entity);
};

#endif
