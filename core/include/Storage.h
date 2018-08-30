#ifndef STORAGE_H
#define STORAGE_H

#include <boost/uuid/uuid.hpp>

#include "Component.h"
#include "Entity.h"
#include "Factory.h"

class IStorage {
    
public:

    virtual Component& operator[](const Entity& entity) = 0;
    virtual Component& Add(Entity& entity) = 0;
    virtual std::optional<std::reference_wrapper<Component>> At(Entity& entity) = 0;
    virtual void Remove(Entity& entity) = 0;
    
};

template <typename T>
class Storage : public IStorage {
    
public:
    
    T& operator[](const Entity& entity) {
        return items_[entity.id];
    }
    
    T& Add(Entity& entity) {
        return items_.Add(entity.id, entity);
    }
    
    std::optional<std::reference_wrapper<T>> At(Entity& entity) {
        return items_.At(entity.id);
    }
    
    void Remove(Entity& entity) {
        return items_.Remove(entity.id);
    }
    
private:
    
    Factory<boost::uuids::uuid, T> items_;
    
};

#endif