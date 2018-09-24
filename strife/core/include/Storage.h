#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include "Component.h"
#include "Entity.h"

namespace Strife {

    class Scene;
    
    class IStorage {
        
    public:
        
        IStorage() = default;
        virtual ~IStorage() = default;
    
        virtual Component* const add(const Entity* const entity) = 0;
        virtual Component* const add(const boost::uuids::uuid id, const Entity* const entity) = 0;
        virtual void remove(const Entity* const entity) = 0;
        virtual Component* const get(const Entity* const entity) const = 0;
        
    };
    
    template <class T>
    class Storage : public IStorage {
        
    public:
            
        T* const add(const Entity* const entity) {
            return &components_.emplace(*entity, entity).first->second;
        };
    
        T* const add(const boost::uuids::uuid id, const Entity* const entity) {
            return &components_.try_emplace(*entity, id, entity).first->second;
        };
        
        void remove(const Entity* const entity) {
            components_.erase(*entity);
        };
        
        T* const get(const Entity* const entity) const {
            return const_cast<T* const>(&components_.at(*entity));
        };
        
    protected:
    
        std::map<Entity, T> components_;
        
    };

}

#endif