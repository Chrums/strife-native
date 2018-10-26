#include "Context.h"

#include "Scene.h"

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
	    Entity entity = scene.entities.add();
	    context_->insert({ id, entity });
	    return entity;
	} else {
	    auto& [ignore, entity] = *iteratorIdToEntity;
	    return entity;
	}
}

optional<Entity> Context::operator[](const string field) {
    const Data identifier = data[field];
    if (!identifier.is_null()) {
        const uuid id = identifier.get<uuid>();
    	return at(id);
    } else {
        return nullopt;
    }
}

Context Context::bind(const Data data) {
    return Context(scene, context_, data);
}

Context::Context(Scene& scene, map<uuid, Entity>* context, const Data data)
    : scene(scene)
    , context_(context)
    , data(data) {}