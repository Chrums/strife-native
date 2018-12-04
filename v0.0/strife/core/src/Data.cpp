#include "Data.h"

#include <iostream>
#include <exception>
#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;
using nlohmann::json;

// Data::Context::Context(Scene* const scene)
//     : scene_(scene) {};

// Entity Data::Context::get(const uuid id) {
//     auto iteratorIdToEntity = context_.find(id);
// 	if (iteratorIdToEntity == context_.end()) {
// 	    Entity entity = scene_->entities.add();
// 	    context_.insert({ id, entity });
// 	    return entity;
// 	} else {
// 	    auto& [ignore, entity] = *iteratorIdToEntity;
// 	    return entity;
// 	}
// }

// Data::Data()
//     : json() {}
    
// Data::Data(const Data& data)
//     : json(static_cast<const json&>(data)) {
//     m_data = data.m_data;
// }
    
// Data::Data(Scene* const scene)
//     : json() {
//     m_data = reinterpret_cast<void*>(new Context(scene));
// }
    
// Data::Data(const json& j)
//     : json(j) {}
    
// Data& Data::bind(Scene* const scene) {
//     m_data = reinterpret_cast<void*>(new Context(scene));
// }

Entity basic_json::entity(const uuid id) {
    if (scene_ != nullptr && context_ != nullptr) {
        auto iteratorIdToEntity = context_.find(id);
    	if (iteratorIdToEntity == context_.end()) {
    	    Entity entity = scene_->entities.add();
    	    context_.insert({ id, entity });
    	    return entity;
    	} else {
    	    auto& [ignore, entity] = *iteratorIdToEntity;
    	    return entity;
    	}
    } else {
        throw std::invalid_argument("Attempting to access context on stateless Data object.");
    }
}

Change basic_json to be not templated