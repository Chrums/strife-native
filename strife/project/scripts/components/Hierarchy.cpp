#include <iostream>
#include <fstream>

#include <boost/filesystem/path.hpp>

#include "Data.h"
#include "Hierarchy.h"
#include "Transform.h"
#include "systems/SpriteAnimation.h"
#include "Scene.h"
#include "EntityMap.h"
#include "events/ParentChanged.h"
#include "Engine.h"

using namespace std;
using namespace Strife::Core;

const string Hierarchy::Identifier = "Hierarchy";

void Hierarchy::Initialize(System<Hierarchy>& system) {
	//system.on<RenderEvent>(&Sprite::render);
}

Hierarchy::Hierarchy(const Strife::Core::Entity& entity)
    : Component(entity)
    , parent_(nullopt) {}

Hierarchy::Hierarchy(const boost::uuids::uuid id, const Strife::Core::Entity& entity)
    : Component(id, entity)
    , parent_(nullopt) {}

const Data Hierarchy::serialize() const {
	Data data;
	if (parent_.has_value()) {
		data["parent"] = parent_.value().id;
	} else {
		Data null;
		data["parent"] = null;
	}
	return data;
}

void Hierarchy::deserialize(Data data, EntityMap& entityMap) {
	if (data["parent"].type() == Data::value_t::null) {
		setParent(nullopt);
	} else {
		setParent(entityMap.getEntity(data["parent"]));
	}
}

void Hierarchy::setParent(optional<Entity> parent) {
	if (parent_ != parent) {
		optional<Entity> oldParent = parent_;
		parent_ = parent;
		Engine::Instance()->dispatcher.emit<ParentChanged>(entity, oldParent, parent);
	}
}

std::optional<Entity> Hierarchy::getParent() {
	return parent_;
}
