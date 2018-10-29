#include "Data.h"

#include <iostream>
#include <exception>
#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

Data::Data()
    : json()
    , scene_(nullptr)
    , context_(nullptr) {}
    
Data::Data(const Data& data)
    : json(static_cast<const json&>(data))
    , scene_(data.scene_)
    , context_(data.context_) {}
    
Data::Data(Scene* const scene)
    : json()
    , scene_(scene)
    , context_(make_shared<map<uuid, Entity>>()) {}
    
Data::Data(const json& j)
    : json(j)
    , scene_(nullptr)
    , context_(nullptr) {}

Entity Data::get(const uuid id) {
    if (context_) {
        auto iteratorIdToEntity = context_->find(id);
    	if (iteratorIdToEntity == context_->end()) {
    	    Entity entity = scene_->entities.add();
    	    context_->insert({ id, entity });
    	    return entity;
    	} else {
    	    auto& [ignore, entity] = *iteratorIdToEntity;
    	    return entity;
    	}
    } else {
        throw std::invalid_argument("Attempting to access context on static Data object.");
    }
}

Data Data::bind(const Data& data) {
    if (context_) {
        return Data(scene_, context_, static_cast<const json&>(data));
    } else {
        throw std::invalid_argument("Attempting to access context on static Data object.");
    }
}

Data::Data(Scene* const scene, shared_ptr<map<uuid, Entity>> context, const json& j)
    : json(j)
    , scene_(scene)
    , context_(context) {}