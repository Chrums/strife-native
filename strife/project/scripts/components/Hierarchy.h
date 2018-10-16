#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <optional>

#include "Component.h"
#include "Data.h"
#include "Entity.h"
#include "System.h"
#include "Event.h"
#include "events/RenderEvent.h"
#include "EntityMap.h"
#include "systems/SpriteAnimation.h"

class Hierarchy : public Strife::Core::Component {

public:
	static void Initialize(Strife::Core::System<Hierarchy>& system);

	static const std::string Identifier;

	Hierarchy(const Strife::Core::Entity& entity);

	Hierarchy(const boost::uuids::uuid id, const Strife::Core::Entity& entity);

	const Strife::Core::Data serialize() const;

	void deserialize(Strife::Core::Data data, Strife::Core::EntityMap& entityMap);

	void setParent(std::optional<Strife::Core::Entity> parent);

	std::optional<Strife::Core::Entity> getParent();

private:
	std::optional<Strife::Core::Entity> parent_;
};

#endif  // SPRITE_H
