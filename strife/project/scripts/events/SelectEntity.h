#ifndef SELECTENTITY_H
#define SELECTENTITY_H

#include "Event.h"
#include "Entity.h"
#include <optional>

class SelectEntity : public Strife::Core::Event {

public:

	static const unsigned int Priority;

	SelectEntity(const std::optional<Strife::Core::Entity> entity)
	    : entity(entity) {}

	SelectEntity(const Strife::Core::Event target, const std::optional<Strife::Core::Entity> entity)
	    : Event(target)
	    , entity(entity) {}

	std::optional<Strife::Core::Entity> entity;

};

#endif  // RENDEREVENT_H
