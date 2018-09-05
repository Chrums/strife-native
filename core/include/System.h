#ifndef System_H
#define System_H

#include <map>

#include <boost/uuid/uuid.hpp>

#include "Component.h"
#include "Entity.h"

class ISystem {
    
public:
    
    virtual void Initialize(void) = 0;
    virtual void Update(void) = 0;
    virtual void Render(void) = 0;

    virtual Component* Add(Entity* entity) = 0;
    virtual void Remove(Entity* entity) = 0;
    virtual Component* At(Entity* entity) = 0;
    
};

template <typename T>
class System : public ISystem {
    
public:
    
    void Initialize(void) {};
    
    void Update(void) {
        for (auto& it : items_) {
            it.second.Update();
        }
    };
    
    void Render(void) {
        for (auto& it : items_) {
            it.second.Render();
        }
    };
    
    T* Add(Entity* entity) {
        T* component = &items_.emplace(entity->id, entity).first->second;
        component->Initialize();
        return component;
    };
    
    void Remove(Entity* entity) {
        items_.erase(entity->id);
    };
    
    T* At(Entity* entity) {
        return &items_.at(entity->id);
    };
    
private:
    
    std::map<boost::uuids::uuid, T> items_;
    
};

#endif