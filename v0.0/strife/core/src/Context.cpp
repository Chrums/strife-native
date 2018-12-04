// #include "Context.h"

// #include <exception>
// #include "Scene.h"

// using namespace Strife::Core;
// using namespace std;
// using boost::uuids::uuid;
// using nlohmann::json;

// Context::Context()
//     : scene_(nullptr)
//     , context_(nullptr) {}

// Context::Context(Scene* scene)
//     : scene_(scene)
//     , context_(make_shared<map<uuid, Entity>>()) {}
    
// Entity Context::get(const uuid id) {
//     if (context_) {
//         auto iteratorIdToEntity = context_->find(id);
//     	if (iteratorIdToEntity == context_->end()) {
//     	    Entity entity = scene_->entities.add();
//     	    context_->insert({ id, entity });
//     	    return entity;
//     	} else {
//     	    auto& [ignore, entity] = *iteratorIdToEntity;
//     	    return entity;
//     	}
//     } else {
//         throw std::invalid_argument("Attempting to access context on static Data object.");
//     }
// }

// Context::Accessor Context::operator[](const std::string identifier) {
//     return Accessor(*this, identifier);
// }

// Context Context::bind(const json data) {
//     if (context_) {
//         return Context(scene_, context_, data);
//     } else {
//         throw std::invalid_argument("Attempting to access context on static Data object.");
//     }
// }

// Context::Context(Scene* scene, shared_ptr<map<uuid, Entity>> context, const json data)
//     : scene_(scene)
//     , context_(context)
//     , data(data) {}