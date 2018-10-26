#include "Context.h"

#include "Scene.h"

using namespace Strife::Core;
using namespace std;
using boost::uuids::uuid;

Context::Context(Scene& scene)
    : scene(scene)
    , context_(make_shared<map<uuid, Entity>>()) {}
    
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

Context Context::bind(const Data data) {
    return Context(scene, context_, data);
}

Context::Context(Scene& scene, shared_ptr<map<uuid, Entity>> context, const Data data)
    : scene(scene)
    , context_(context)
    , data(data) {}