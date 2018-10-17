#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "ISystem.h"
#include "Dispatcher.h"
#include "events/OnGui.h"
#include <SDL.h>
#include <typeindex>

class Scene;

class EntityList : public Strife::Core::ISystem {
public:
	EntityList(Strife::Core::Scene& scene, Strife::Core::Dispatcher& dispatcher);

	~EntityList();

	void render(const OnGui& event);

private:
	bool active_;

	std::type_index addComponentType_;
};

#endif
