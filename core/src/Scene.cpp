#include "Scene.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using boost::property_tree::ptree;
using boost::uuids::uuid;

void Scene::Initialize(void) {
    for (auto& it : systems_) {
        //it.second->Initialize();
    }
}

void Scene::Update(void) {
    update();
}

void Scene::Render(void) {
    render();
}

// ptree Scene::Serialize(void) {
//     return ptree();
// }

void Scene::Deserialize(ptree data) {
    
    auto entities = data.get_child("entities");
    for (ptree::value_type &entity : entities) {
        string id = entity.second.data();
        AddEntity(boost::lexical_cast<uuid>(id));
    }
    
    auto systems = data.get_child("systems");
    for (ptree::value_type &system : systems) {
        std::type_index type = identifierToType_.at(system.first);
        for (ptree::value_type &entityComponents : system.second) {
            for (ptree::value_type &component : entityComponents.second) {
                Component* c = AddComponentByTypeAndEntity(type, GetEntityById(boost::lexical_cast<uuid>(entityComponents.first)));
                //c->Deserialize(component.second.data());
            }
        }
    }
    
}

Entity* Scene::AddEntity(void) {
    Entity temp(this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

Entity* Scene::AddEntity(boost::uuids::uuid id) {
    Entity temp(id, this);
    entities_.insert({ temp.id, temp });
    return &entities_.find(temp.id)->second;
};

void Scene::RemoveEntity(Entity* entity) {
    
    // Remove entity from scene
    entities_.erase(entity->id);
    
    // TODO: Remove all components...
    
};

Entity* Scene::GetEntityById(const boost::uuids::uuid id) {
    auto search = entities_.find(id);
    return search != entities_.end()
        ? &search->second
        : nullptr;
};

Component* Scene::AddComponentByTypeAndEntity(std::type_index type, Entity* entity) {
    return systems_[type]->Add(entity);
};

void Scene::RemoveComponentByTypeAndEntity(std::type_index type, Entity* entity) {
    systems_[type]->Remove(entity);
};

Component* Scene::GetComponentByTypeAndEntity(std::type_index type, Entity* entity) {
    return systems_[type]->At(entity);
};