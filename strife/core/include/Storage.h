#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Component.h"
#include "Data.h"
#include "Entity.h"

namespace Strife {
    namespace Core {
    
        class Scene;
        
        class IStorage {
            
        public:
        
            IStorage(Scene* const scene) :
                scene_(scene) {};
                
            virtual ~IStorage() = default;
            
            virtual const Data serialize() const = 0;
            virtual void deserialize(const Data data) = 0;
        
            virtual Component* const add(const Entity entity) = 0;
            virtual Component* const add(const boost::uuids::uuid id, const Entity entity) = 0;
            virtual void remove(const Entity entity) = 0;
            virtual Component* const get(const Entity entity) const = 0;
            
        protected:
            
            Scene* const scene_;
            
        };
        
        template <class T>
        class Storage : public IStorage, private std::map<Entity, T> {
            
        public:
        
            Storage(Scene* const scene) :
                IStorage(scene) {};
        
            const Data serialize() const {
                Data data;
                for (const auto& pairEntityToComponent : *this) {
                    const Entity entity = pairEntityToComponent.first;
                    const T component = pairEntityToComponent.second;
                    const std::string entityIdentifier = boost::lexical_cast<std::string>(entity.id);
                    const Data componentData = component.serialize();
                    data[entityIdentifier] = componentData;
                }
                return data;
            };
            
            void deserialize(const Data data) {
                for (Data::const_iterator iteratorEntityIdentifierToComponentData = data.begin(); iteratorEntityIdentifierToComponentData != data.end(); iteratorEntityIdentifierToComponentData++) {
                    const std::string entityIdentifier = iteratorEntityIdentifierToComponentData.key();
                    const Data componentData = iteratorEntityIdentifierToComponentData.value();
                    const boost::uuids::uuid entityId = boost::lexical_cast<boost::uuids::uuid>(entityIdentifier);
                    const Entity entity(entityId, scene_);
                    T* const component = add(entity);
                    component->deserialize(componentData);
                }
            };
                
            T* const add(const Entity entity) {
                return &this->emplace(entity, entity).first->second;
            };
        
            T* const add(const boost::uuids::uuid id, const Entity entity) {
                return &this->try_emplace(entity, id, entity).first->second;
            };
            
            void remove(const Entity entity) {
                this->erase(entity);
            };
            
            T* const get(const Entity entity) const {
                return const_cast<T* const>(&this->at(entity));
            };
            
        };
    
    }
}

#endif