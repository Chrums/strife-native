#include "Scene.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using boost::property_tree::ptree;
using boost::uuids::uuid;

void Scene::initialize(void) {
    
}

void Scene::update(void) {
    updates();
}

void Scene::render(void) {
    renders();
}

// ptree Scene::serialize(void) {
//     return ptree();
// }

void Scene::deserialize(ptree data) {
    
    auto entities = data.get_child("entities");
    for (ptree::value_type &entity : entities) {
        string id = entity.second.data();
        addEntity(boost::lexical_cast<uuid>(id));
    }
    
    auto systems = data.get_child("systems");
    for (ptree::value_type &system : systems) {
        type_index type = identifierToType_.at(system.first);
        for (ptree::value_type &entityComponents : system.second) {
            for (ptree::value_type &component : entityComponents.second) {
                Component* c = addComponent(type, getEntity(boost::lexical_cast<uuid>(entityComponents.first)));
                //c->Deserialize(component.second.data());
            }
        }
    }
    
}

Entity* Scene::addEntity() {
    Entity temp(this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

Entity* Scene::addEntity(const uuid id) {
    Entity temp(id, this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

void Scene::removeEntity(Entity* entity) {
    entities_.erase(entity->id);
    for (auto it : systems_) {
        it.second->remove(entity);
    }
};

Entity* Scene::getEntity(const uuid id) {
    auto search = entities_.find(id);
    return search != entities_.end()
        ? &search->second
        : nullptr;
};

Component* Scene::addComponent(std::type_index type, Entity* entity) {
    return systems_[type]->add(entity);
};

void Scene::removeComponent(std::type_index type, Entity* entity) {
    systems_[type]->remove(entity);
};

Component* Scene::getComponent(std::type_index type, Entity* entity) {
    return systems_[type]->at(entity);
};