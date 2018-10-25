#include "Context.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

Context::Context(Scene& scene)
    : scene(scene)
    , context_(new map<uuid, Entity>()) {}
    
void Context::destroy() {
    delete context_;
}

Entity Context::at(const uuid id) {
	auto iteratorIdToEntity = context_->find(id);
	if (iteratorIdToEntity == context_->end()) {
	    auto [ignore, entity] = *context_->try_emplace(id, scene).first;
	    return entity;
	} else {
	    auto& [ignore, entity] = *iteratorIdToEntity;
	    return entity;
	}
}

Context Context::bind(const Data data) {
    return Context(scene, context_, data);
}

Context::Context(Scene& scene, map<uuid, Entity>* context, const Data data)
    : scene(scene)
    , context_(context)
    , data(data) {}