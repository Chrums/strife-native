#ifndef ENTITY_H
#define ENTITY_H

#include <set>
#include <typeindex>
#include <boost/uuid/uuid.hpp>
#include "Component.h"
#include "Unique.h"

namespace Strife {
    
    class Scene;
    
    class Entity : public Unique {
        
        class Components {
            
        public:
            
            Components(const Entity* const entity);
            
            Component* const add(const std::type_index type) const;
            Component* const add(const std::type_index type, const boost::uuids::uuid id) const;
            void remove(const std::type_index type) const;
            Component* const get(const std::type_index type) const;
        
            template <class T>
            T* const add() const {
                return static_cast<T* const>(add(std::type_index(typeid(T))));
            };
            
            template <class T>
            T* const add(const boost::uuids::uuid id) const {
                return static_cast<T* const>(add(std::type_index(typeid(T)), id));
            };
            
            template <class T>
            void remove() const {
                remove(std::type_index(typeid(T)));
            };
            
            template <class T>
            T* const get() const {
                return static_cast<T* const>(get(std::type_index(typeid(T))));
            };
            
        private:
            
            const Entity* const entity_;
            
        };
        
    public:
        
        Scene* const scene;
        const Components components;
        
        Entity(const Entity& entity);
        Entity(Scene* const scene);
        Entity(const boost::uuids::uuid id, Scene* const scene);
    
    };
    
}

#endif