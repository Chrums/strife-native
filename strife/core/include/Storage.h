#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Component.h"
#include "Entity.h"

namespace Strife {

    class Scene;
    
    class IStorage {
        
    public:
    
        IStorage() = default;
        virtual ~IStorage() = default;
        
        virtual const nlohmann::json serialize() const = 0;
        virtual void deserialize(const nlohmann::json data) = 0;
    
        virtual Component* const add(const Entity entity) = 0;
        virtual Component* const add(const boost::uuids::uuid id, const Entity entity) = 0;
        virtual void remove(const Entity entity) = 0;
        virtual Component* const get(const Entity entity) const = 0;
        
    };
    
    template <class T>
    class Storage : public IStorage, private std::map<Entity, T> {
        
    public:
    
        const nlohmann::json serialize() const {
            nlohmann::json data;
            for (const auto& pairEntityToComponent : *this) {
                const Entity entity = pairEntityToComponent.first;
                const Component component = pairEntityToComponent.second;
                const std::string entityIdentifier = boost::lexical_cast<std::string>(entity.id);
                const nlohmann::json componentData = component.serialize();
                data[entityIdentifier] = componentData;
            }
            return data;
        };
        
        void deserialize(const nlohmann::json data) {
            
        };
            
        T* const add(const Entity entity) {
            return &(*this).emplace(entity, entity).first->second;
        };
    
        T* const add(const boost::uuids::uuid id, const Entity entity) {
            return &(*this).try_emplace(entity, id, entity).first->second;
        };
        
        void remove(const Entity entity) {
            (*this).erase(entity);
        };
        
        T* const get(const Entity entity) const {
            return const_cast<T* const>(&(*this).at(entity));
        };
        
    };

}

#endif