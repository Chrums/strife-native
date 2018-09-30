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
    class Storage : public IStorage, private std::map<Entity, T> {
        
    public:
            
        T* const add(const Entity* const entity) {
            return &(*this).emplace(*entity, entity).first->second;
        };
    
        T* const add(const boost::uuids::uuid id, const Entity* const entity) {
            return &(*this).try_emplace(*entity, id, entity).first->second;
        };
        
        void remove(const Entity* const entity) {
            (*this).erase(*entity);
        };
        
        T* const get(const Entity* const entity) const {
            return const_cast<T* const>(&(*this).at(*entity));
        };
        
    };

}

#endif