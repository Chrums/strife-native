#ifndef PARENTCHANGED_H
#define PARENTCHANGED_H

#include "Event.h"
#include "Entity.h"

class ParentChanged : public Strife::Core::Event {

public:

	static const unsigned int Priority;

	ParentChanged(const Strife::Core::Entity changedEntity,
	              const std::optional<Strife::Core::Entity> previousParent,
	              const std::optional<Strife::Core::Entity> newParent)
	    : changedEntity(changedEntity)
	    , previousParent(previousParent)
	    , newParent(newParent) {}

	ParentChanged(const Strife::Core::Entity target,
	              const Strife::Core::Entity changedEntity,
	              const std::optional<Strife::Core::Entity> previousParent,
	              const std::optional<Strife::Core::Entity> newParent)
	    : Event(target)
	    , changedEntity(changedEntity)
	    , previousParent(previousParent)
	    , newParent(newParent) {}

	const Strife::Core::Entity changedEntity;
	const std::optional<Strife::Core::Entity> previousParent;
	const std::optional<Strife::Core::Entity> newParent;

};

#endif
