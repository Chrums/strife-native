#ifndef STORAGE_H
#define STORAGE_H

#include <map>

#include <boost/uuid/uuid.hpp>

#include "Component.h"
#include "Entity.h"

class IStorage {
    
public:

    virtual Component* Add(Entity* entity) = 0;
    virtual void Remove(Entity* entity) = 0;
    virtual Component* At(Entity* entity) = 0;
    
};

template <typename T>
class Storage : public IStorage {
    
public:
    
    T* Add(Entity* entity) {
        return &items_.emplace(entity->id, entity).first->second;
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